#include <sai.h>




extern int8_t saiDMATransmitBuffer[MY_DMA_BUFFER_SIZE_BYTES];


extern int8_t saiDMAReceiveBuffer[MY_DMA_BUFFER_SIZE_BYTES];

static SAI_HandleTypeDef haudio_out_sai;
static SAI_HandleTypeDef haudio_in_sai;

static WM8994_Object_t   WM8994Obj;
static AUDIO_Drv_t                     *Audio_Drv = NULL;

void audio_init(uint32_t frequency){


	 // fill_buffer_with_square_wave(playbackBuffer, MY_BUFFER_SIZE_SAMPLES);
	 // ConvertSampleBufferToDMABuffer(playbackBuffer, (uint8_t*)saiDMATransmitBuffer, MY_BUFFER_SIZE_SAMPLES);


	  haudio_out_sai.Instance = SAI2_Block_A;
	  haudio_in_sai.Instance = SAI2_Block_B;
	  My_SAI_ClockConfig(frequency);
	  My_AUDIO_OUT_MspInit();
	  My_SAI_Out_Init(frequency);
	  My_AUDIO_IN_MspInit();
	  My_SAI_In_Init(frequency);

	  WM8994_Probe();
	  WM8994_Init_t codec_init;
	  codec_init.Resolution  =  0;

	   /* Fill codec_init structure */
	   codec_init.Frequency    = frequency;
	   codec_init.InputDevice  = WM8994_IN_LINE1;
	   codec_init.OutputDevice = AUDIO_OUT_DEVICE_HEADPHONE;

	   /* Convert volume before sending to the codec */
	   codec_init.Volume       = VOLUME_IN_CONVERT(74);//mettre le volume à 74 permet d'avoir la même amplitude que le signal d'entrée

	    /* Initialize the codec internal registers */
	    WM8994_Init(&WM8994Obj, &codec_init);
	    HAL_SAI_Transmit_DMA(&haudio_out_sai, (uint8_t*)saiDMATransmitBuffer, MY_DMA_BUFFER_SIZE_MSIZES);
	    HAL_SAI_Receive_DMA(&haudio_in_sai, (uint8_t*)saiDMAReceiveBuffer, MY_DMA_BUFFER_SIZE_MSIZES);


}

void My_AUDIO_OUT_MspInit(void){
	GPIO_InitTypeDef gpio_init_structure;
	  extern DMA_HandleTypeDef hdma_sai_tx;

	  /* Enable SAI clock */
	  AUDIO_OUT_SAIx_CLK_ENABLE();

	  /* Enable GPIO clock */
	  AUDIO_OUT_SAIx_SCK_ENABLE();
	  AUDIO_OUT_SAIx_SD_ENABLE();
	  AUDIO_OUT_SAIx_FS_ENABLE();
	  /* CODEC_SAI pins configuration: FS, SCK, MCK and SD pins ------------------*/
	  gpio_init_structure.Pin = AUDIO_OUT_SAIx_FS_PIN;
	  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
	  gpio_init_structure.Pull = GPIO_NOPULL;
	  gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  gpio_init_structure.Alternate = AUDIO_OUT_SAIx_FS_AF;
	  HAL_GPIO_Init(AUDIO_OUT_SAIx_FS_GPIO_PORT, &gpio_init_structure);

	  gpio_init_structure.Pin = AUDIO_OUT_SAIx_SCK_PIN;
	  gpio_init_structure.Alternate = AUDIO_OUT_SAIx_SCK_AF;
	  HAL_GPIO_Init(AUDIO_OUT_SAIx_SCK_GPIO_PORT, &gpio_init_structure);

	  gpio_init_structure.Pin = AUDIO_OUT_SAIx_SD_PIN;
	  gpio_init_structure.Alternate = AUDIO_OUT_SAIx_SD_AF;
	  HAL_GPIO_Init(AUDIO_OUT_SAIx_SD_GPIO_PORT, &gpio_init_structure);

	    /* Enable the DMA clock */
	    AUDIO_OUT_SAIx_DMAx_CLK_ENABLE();

	      hdma_sai_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	      hdma_sai_tx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;

	    hdma_sai_tx.Init.Request = AUDIO_OUT_SAIx_DMAx_REQUEST;
	    hdma_sai_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	    hdma_sai_tx.Init.MemInc = DMA_MINC_ENABLE;
	    hdma_sai_tx.Init.Mode = DMA_CIRCULAR;
	    hdma_sai_tx.Init.Priority = DMA_PRIORITY_HIGH;
	    hdma_sai_tx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
	    hdma_sai_tx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	    hdma_sai_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	    hdma_sai_tx.Instance = AUDIO_OUT_SAIx_DMAx_STREAM;
	    hdma_sai_tx.Init.MemBurst = DMA_MBURST_SINGLE;
	    hdma_sai_tx.Init.PeriphBurst = DMA_PBURST_SINGLE;

	    /* Associate the DMA handle */
	    __HAL_LINKDMA(&haudio_out_sai, hdmatx, hdma_sai_tx);


	    /* Deinitialize the Stream for new transfer */
	    (void)HAL_DMA_DeInit(&hdma_sai_tx);

	    /* Configure the DMA Stream */
	    (void)HAL_DMA_Init(&hdma_sai_tx);

	    /* SAI DMA IRQ Channel configuration */
	    HAL_NVIC_SetPriority(AUDIO_OUT_SAIx_DMAx_IRQ, AUDIO_OUT_IRQ_PREPRIO, 0);
	    HAL_NVIC_EnableIRQ(AUDIO_OUT_SAIx_DMAx_IRQ);


}

void fill_buffer_with_square_wave(int16_t * buf, uint32_t num_samples){
	int toggle_period=240;
	int count=0;
	int wave_state=1;
	int magnitude=30000;
	for (int i=0; i<num_samples;i++){
		buf[i]=magnitude*wave_state;
		count ++;
		if(count >=toggle_period){
			count=0;
			wave_state=wave_state*(-1);
		}
	}
}


//frame length 8 bytes, ie. samples are spaced 8 bytes apart
//sample size 2 bytes
//frame is every 8 bytes, data appears at the 1st and 4th, left and right channel
//for now just take 1 channel when extracting, and duplicate both channels when inserting
void ConvertSampleBufferToDMABuffer(int16_t * sampleBuffer, uint8_t *dmaBuffer, uint32_t num_samples){
	for(uint32_t i=0;i<num_samples;i++){
		int16_t * p=(int16_t*) &dmaBuffer[i*8]; //samples are spaced 8 bytes apart
		*p=sampleBuffer[i];
		*(p+2)=sampleBuffer[i];
	}
}

HAL_StatusTypeDef My_SAI_ClockConfig(uint32_t AudioFreq){

	RCC_PeriphCLKInitTypeDef rcc_ex_clk_init_struct;

	  HAL_RCCEx_GetPeriphCLKConfig(&rcc_ex_clk_init_struct);

	  /* Set the PLL configuration according to the audio frequency */
	  if((AudioFreq == AUDIO_FREQUENCY_11K) || (AudioFreq == AUDIO_FREQUENCY_22K) || (AudioFreq == AUDIO_FREQUENCY_44K))
	  {
	    /* SAI clock config:
	    PLL2_VCO Input = HSE_VALUE/PLL2M = 1 Mhz
	    PLL2_VCO Output = PLL2_VCO Input * PLL2N = 429 Mhz
	    SAI_CLK_x = PLL2_VCO Output/PLL2P = 429/38 = 11.289 Mhz */
	    rcc_ex_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_SAI2;
	    rcc_ex_clk_init_struct.Sai23ClockSelection = RCC_SAI2CLKSOURCE_PLL2;
	    rcc_ex_clk_init_struct.PLL2.PLL2P = 38;
	    rcc_ex_clk_init_struct.PLL2.PLL2N = 429;

	  }
	  else /* AUDIO_FREQUENCY_8K, AUDIO_FREQUENCY_16K, AUDIO_FREQUENCY_48K, AUDIO_FREQUENCY_96K */
	  {
	    /* SAI clock config:
	    PLL2_VCO Input = HSE_VALUE/PLL2M = 1 Mhz
	    PLL2_VCO Output = PLL2_VCO Input * PLL2N = 344 Mhz
	    SAI_CLK_x = PLL2_VCO Output/PLL2P = 344/7 = 49.142 Mhz */
	    rcc_ex_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_SAI2;
	    rcc_ex_clk_init_struct.Sai23ClockSelection = RCC_SAI2CLKSOURCE_PLL2;
	    rcc_ex_clk_init_struct.PLL2.PLL2P = 7;
	    rcc_ex_clk_init_struct.PLL2.PLL2N = 344;

	  }
	  rcc_ex_clk_init_struct.PLL2.PLL2Q = 1;
	  rcc_ex_clk_init_struct.PLL2.PLL2R = 1;
	  rcc_ex_clk_init_struct.PLL2.PLL2M = 25;
	  return  HAL_RCCEx_PeriphCLKConfig(&rcc_ex_clk_init_struct);
}

void My_SAI_Out_Init(uint32_t AudioFreq)
{

	  /* Disable SAI peripheral to allow access to SAI internal registers */
	  __HAL_SAI_DISABLE(&haudio_out_sai);

	  /* Configure SAI_Block_x
	  LSBFirst: Disabled
	  DataSize: 16 */
	  haudio_out_sai.Init.MonoStereoMode = SAI_STEREOMODE;
	  haudio_out_sai.Init.AudioFrequency = AudioFreq;
	  haudio_out_sai.Init.AudioMode = SAI_MODEMASTER_TX;
	  haudio_out_sai.Init.NoDivider = SAI_MASTERDIVIDER_ENABLED;
	  haudio_out_sai.Init.Protocol = SAI_FREE_PROTOCOL;
	  haudio_out_sai.Init.DataSize = SAI_DATASIZE_16;
	  haudio_out_sai.Init.FirstBit = SAI_FIRSTBIT_MSB;
	  haudio_out_sai.Init.ClockStrobing = SAI_CLOCKSTROBING_FALLINGEDGE;
	  haudio_out_sai.Init.Synchro = SAI_ASYNCHRONOUS;
	  haudio_out_sai.Init.OutputDrive = SAI_OUTPUTDRIVE_ENABLED;
	  haudio_out_sai.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_1QF;
	  haudio_out_sai.Init.SynchroExt     = SAI_SYNCEXT_DISABLE;
	  haudio_out_sai.Init.CompandingMode = SAI_NOCOMPANDING;
	  haudio_out_sai.Init.TriState       = SAI_OUTPUT_NOTRELEASED;
	  haudio_out_sai.Init.Mckdiv         = 0;

	  /* Configure SAI_Block_x Frame
	  Frame Length: 64
	  Frame active Length: 32
	  FS Definition: Start frame + Channel Side identification
	  FS Polarity: FS active Low
	  FS Offset: FS asserted one bit before the first bit of slot 0 */
	  haudio_out_sai.FrameInit.FrameLength = 64;
	  haudio_out_sai.FrameInit.ActiveFrameLength = 32;
	  haudio_out_sai.FrameInit.FSDefinition = SAI_FS_CHANNEL_IDENTIFICATION;
	  haudio_out_sai.FrameInit.FSPolarity = SAI_FS_ACTIVE_LOW;
	  haudio_out_sai.FrameInit.FSOffset = SAI_FS_BEFOREFIRSTBIT;

	  /* Configure SAI Block_x Slot
	  Slot First Bit Offset: 0
	  Slot Size  : 16
	  Slot Number: 4
	  Slot Active: All slot actives */
	  haudio_out_sai.SlotInit.FirstBitOffset = 0;
	  haudio_out_sai.SlotInit.SlotSize = SAI_SLOTSIZE_DATASIZE;
	  haudio_out_sai.SlotInit.SlotNumber = 4;
	  haudio_out_sai.SlotInit.SlotActive = 0xF;

	  HAL_SAI_Init(&haudio_out_sai);

	  /* Enable SAI peripheral to generate MCLK */
	  __HAL_SAI_ENABLE(&haudio_out_sai);
}

 int32_t WM8994_Probe(void)
{
	int32_t ret = BSP_ERROR_NONE;
  WM8994_IO_t              IOCtx;

  uint32_t id;

  /* Configure the audio driver */
  IOCtx.Address     = AUDIO_I2C_ADDRESS;
  IOCtx.Init        = BSP_I2C4_Init;
  IOCtx.DeInit      = BSP_I2C4_DeInit;
  IOCtx.ReadReg     = BSP_I2C4_ReadReg16;
  IOCtx.WriteReg    = BSP_I2C4_WriteReg16;
  IOCtx.GetTick     = BSP_GetTick;

  if(WM8994_RegisterBusIO (&WM8994Obj, &IOCtx) != WM8994_OK)
  {
    ret = BSP_ERROR_BUS_FAILURE;
  }
  else
  {
    /* Reset the codec */
    if(WM8994_Reset(&WM8994Obj) != WM8994_OK)
    {
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }
    else if(WM8994_ReadID(&WM8994Obj, &id) != WM8994_OK)
    {
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }
    else if(id != WM8994_ID)
    {
      ret = BSP_ERROR_UNKNOWN_COMPONENT;
    }
    else
    {
      Audio_Drv = (AUDIO_Drv_t *) &WM8994_Driver;

    }
  }
  return ret;
}

void My_AUDIO_IN_MspInit(void)
{extern DMA_HandleTypeDef hdma_sai_rx;
GPIO_InitTypeDef  gpio_init_structure;

/* Enable SAI clock */
    AUDIO_IN_SAIx_CLK_ENABLE();

    /* Enable SD GPIO clock */
    AUDIO_IN_SAIx_SD_ENABLE();
    /* CODEC_SAI pin configuration: SD pin */
    gpio_init_structure.Pin = AUDIO_IN_SAIx_SD_PIN;
    gpio_init_structure.Mode = GPIO_MODE_AF_PP;
    gpio_init_structure.Pull = GPIO_NOPULL;
    gpio_init_structure.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init_structure.Alternate = AUDIO_IN_SAIx_AF;
    HAL_GPIO_Init(AUDIO_IN_SAIx_SD_GPIO_PORT, &gpio_init_structure);

    /* Enable the DMA clock */
    AUDIO_IN_SAIx_DMAx_CLK_ENABLE();

    /* Configure the hdma_sai_rx handle parameters */
    hdma_sai_rx.Instance = AUDIO_IN_SAIx_DMAx_STREAM;
    hdma_sai_rx.Init.Request = AUDIO_IN_SAIx_DMAx_REQUEST;
    hdma_sai_rx.Init.Mode = DMA_CIRCULAR;
    hdma_sai_rx.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_sai_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_sai_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_sai_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_sai_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    hdma_sai_rx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    hdma_sai_rx.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_sai_rx.Init.PeriphBurst = DMA_MBURST_SINGLE;


      hdma_sai_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
      hdma_sai_rx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;

    /* Associate the DMA handle */
    __HAL_LINKDMA(&haudio_in_sai, hdmarx, hdma_sai_rx);


    /* Deinitialize the Stream for new transfer */
    (void)HAL_DMA_DeInit(&hdma_sai_rx);

    /* Configure the DMA Stream */
    (void)HAL_DMA_Init(&hdma_sai_rx);

    /* SAI DMA IRQ Channel configuration */
    HAL_NVIC_SetPriority(AUDIO_IN_SAIx_DMAx_IRQ, AUDIO_IN_IRQ_PREPRIO, 0);
    HAL_NVIC_EnableIRQ(AUDIO_IN_SAIx_DMAx_IRQ);
}

void My_SAI_In_Init(uint32_t AudioFreq)
{
    /* Initialize SAI1 block B in SLAVE RX synchronous from SAI1 block A */
    /* Initialize the haudio_in_sai Instance parameter */
    haudio_in_sai.Instance = AUDIO_IN_SAIx;

    /* Disable SAI peripheral to allow access to SAI internal registers */
    __HAL_SAI_DISABLE(&haudio_in_sai);

    /* Configure SAI_Block_x */
    haudio_in_sai.Init.MonoStereoMode = SAI_STEREOMODE;
    haudio_in_sai.Init.AudioFrequency = AudioFreq;
    haudio_in_sai.Init.AudioMode      = SAI_MODESLAVE_RX;
    haudio_in_sai.Init.NoDivider      = SAI_MASTERDIVIDER_ENABLE;
    haudio_in_sai.Init.Protocol       = SAI_FREE_PROTOCOL;
    haudio_in_sai.Init.DataSize       = SAI_DATASIZE_16;
    haudio_in_sai.Init.FirstBit       = SAI_FIRSTBIT_MSB;
    haudio_in_sai.Init.ClockStrobing  = SAI_CLOCKSTROBING_RISINGEDGE;
    haudio_in_sai.Init.Synchro        = SAI_SYNCHRONOUS;
    haudio_in_sai.Init.OutputDrive    = SAI_OUTPUTDRIVE_DISABLE;
    haudio_in_sai.Init.FIFOThreshold  = SAI_FIFOTHRESHOLD_1QF;
    haudio_in_sai.Init.SynchroExt     = SAI_SYNCEXT_DISABLE;
    haudio_in_sai.Init.CompandingMode = SAI_NOCOMPANDING;
    haudio_in_sai.Init.TriState       = SAI_OUTPUT_RELEASED;
    haudio_in_sai.Init.Mckdiv         = 0;

    /* Configure SAI_Block_x Frame */
    haudio_in_sai.FrameInit.FrameLength       = 64;
    haudio_in_sai.FrameInit.ActiveFrameLength = 32;
    haudio_in_sai.FrameInit.FSDefinition      = SAI_FS_CHANNEL_IDENTIFICATION;
    haudio_in_sai.FrameInit.FSPolarity        = SAI_FS_ACTIVE_LOW;
    haudio_in_sai.FrameInit.FSOffset          = SAI_FS_BEFOREFIRSTBIT;

    /* Configure SAI Block_x Slot */
    haudio_in_sai.SlotInit.FirstBitOffset = 0;
    haudio_in_sai.SlotInit.SlotSize       = SAI_SLOTSIZE_DATASIZE;
    haudio_in_sai.SlotInit.SlotNumber     = 4;
    haudio_in_sai.SlotInit.SlotActive     = 0xF;

    HAL_SAI_Init(&haudio_in_sai);

    /* Enable SAI peripheral */
    __HAL_SAI_ENABLE(&haudio_in_sai);
}

void  LowerHalf_Input_Samples(int16_t * input_samples, uint32_t num_samples)
{
  for(uint32_t i = 0; i<num_samples; i++){
    int16_t * samplePointer = (int16_t *) & saiDMAReceiveBuffer[i*8];
    input_samples[i] = *samplePointer;
  }

}
void  UpperHalf_Input_Samples(int16_t * input_samples,uint32_t num_samples)
{
  for(uint32_t i = 0; i<num_samples; i++){
    int16_t * samplePointer = (int16_t *) & saiDMAReceiveBuffer[(MY_DMA_BUFFER_SIZE_BYTES / 2) + i*8];
    input_samples[i] = *samplePointer;
  }

}
void LowerHalf_Output_Samples(int16_t * output_samples, uint32_t num_samples)
{
  for(uint32_t i=0; i<num_samples; i++){
    int16_t * p = (int16_t *) &saiDMATransmitBuffer[i*8];
    *p = output_samples[i];
    *(p+2) = output_samples[i];
  }
}
void UpperHalf_Output_Samples(int16_t * output_samples, uint32_t num_samples)
{
  for(uint32_t i=0; i<num_samples; i++){
    int16_t * p = (int16_t *) &saiDMATransmitBuffer[(MY_DMA_BUFFER_SIZE_BYTES / 2) + i*8];
    *p = output_samples[i];
    *(p+2) = output_samples[i];
  }
}

void Output_Sample(int16_t sample, int16_t * start, uint32_t pos){

	*(start+4*pos)=sample;
	*(start+4*pos+2)=sample;
}
