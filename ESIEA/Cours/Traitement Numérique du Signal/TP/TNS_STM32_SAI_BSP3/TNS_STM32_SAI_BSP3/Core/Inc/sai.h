#include "stm32h7xx_hal.h"
#include "wm8994.h"
//#include "stm32h750b_discovery_audio.h"
#include "stm32h750b_discovery_bus.h"
#include "stm32h750b_discovery_errno.h"
#define AUDIO_I2C_ADDRESS                0x34U
/* AUDIO FREQUENCY */
#define AUDIO_FREQUENCY_192K     192000U
#define AUDIO_FREQUENCY_176K     176400U
#define AUDIO_FREQUENCY_96K       96000U
#define AUDIO_FREQUENCY_88K       88200U
#define AUDIO_FREQUENCY_48K       48000U
#define AUDIO_FREQUENCY_44K       44100U
#define AUDIO_FREQUENCY_32K       32000U
#define AUDIO_FREQUENCY_22K       22050U
#define AUDIO_FREQUENCY_16K       16000U
#define AUDIO_FREQUENCY_11K       11025U
#define AUDIO_FREQUENCY_8K         8000U

/* AUDIO RESOLUTION */
#define AUDIO_RESOLUTION_16B                16U
#define AUDIO_RESOLUTION_32B                32U

/* Audio Out devices */
#define AUDIO_OUT_DEVICE_NONE               0U
#define AUDIO_OUT_DEVICE_SPEAKER            1U
#define AUDIO_OUT_DEVICE_HEADPHONE          2U
#define AUDIO_OUT_DEVICE_SPK_HP             3U
#define AUDIO_OUT_DEVICE_AUTO               4U


/*------------------------------------------------------------------------------
                          USER SAI defines parameters
 -----------------------------------------------------------------------------*/
/** CODEC_AudioFrame_SLOT_TDMMode In W8994 codec the Audio frame contains 4 slots : TDM Mode
  * TDM format :
  * +------------------|------------------|--------------------|-------------------+
  * | CODEC_SLOT0 Left | CODEC_SLOT1 Left | CODEC_SLOT0 Right  | CODEC_SLOT1 Right |
  * +------------------------------------------------------------------------------+
  */
/* To have 2 separate audio stream in Both headphone and speaker the 4 slot must be activated */
#define CODEC_AUDIOFRAME_SLOT_0123                   SAI_SLOTACTIVE_0 | SAI_SLOTACTIVE_1 | SAI_SLOTACTIVE_2 | SAI_SLOTACTIVE_3
/* To have an audio stream in headphone only SAI Slot 0 and Slot 2 must be activated */
#define CODEC_AUDIOFRAME_SLOT_02                     SAI_SLOTACTIVE_0 | SAI_SLOTACTIVE_2
/* To have an audio stream in speaker only SAI Slot 1 and Slot 3 must be activated */
#define CODEC_AUDIOFRAME_SLOT_13                     SAI_SLOTACTIVE_1 | SAI_SLOTACTIVE_3

/* SAI peripheral configuration defines */
#define AUDIO_OUT_SAIx                           SAI2_Block_A
#define AUDIO_OUT_SAIx_CLK_ENABLE()              __HAL_RCC_SAI2_CLK_ENABLE()
#define AUDIO_OUT_SAIx_CLK_DISABLE()             __HAL_RCC_SAI2_CLK_DISABLE()

#define AUDIO_OUT_SAIx_MCLK_ENABLE()             __HAL_RCC_GPIOI_CLK_ENABLE()
#define AUDIO_OUT_SAIx_MCLK_GPIO_PORT            GPIOI
#define AUDIO_OUT_SAIx_MCLK_PIN                  GPIO_PIN_4
#define AUDIO_OUT_SAIx_MCLK_AF                   GPIO_AF10_SAI2

#define AUDIO_OUT_SAIx_SCK_ENABLE()              __HAL_RCC_GPIOI_CLK_ENABLE()
#define AUDIO_OUT_SAIx_SCK_GPIO_PORT             GPIOI
#define AUDIO_OUT_SAIx_SCK_PIN                   GPIO_PIN_5
#define AUDIO_OUT_SAIx_SCK_AF                    GPIO_AF10_SAI2

#define AUDIO_OUT_SAIx_SD_ENABLE()               __HAL_RCC_GPIOI_CLK_ENABLE()
#define AUDIO_OUT_SAIx_SD_GPIO_PORT              GPIOI
#define AUDIO_OUT_SAIx_SD_PIN                    GPIO_PIN_6
#define AUDIO_OUT_SAIx_SD_AF                     GPIO_AF10_SAI2

#define AUDIO_OUT_SAIx_FS_ENABLE()               __HAL_RCC_GPIOI_CLK_ENABLE()
#define AUDIO_OUT_SAIx_FS_GPIO_PORT              GPIOI
#define AUDIO_OUT_SAIx_FS_PIN                    GPIO_PIN_7
#define AUDIO_OUT_SAIx_FS_AF                     GPIO_AF10_SAI2

/* SAI DMA Stream definitions */
#define AUDIO_OUT_SAIx_DMAx_CLK_ENABLE()         __HAL_RCC_DMA2_CLK_ENABLE()
#define AUDIO_OUT_SAIx_DMAx_STREAM               DMA2_Stream1
#define AUDIO_OUT_SAIx_DMAx_REQUEST              DMA_REQUEST_SAI2_A
#define AUDIO_OUT_SAIx_DMAx_IRQ                  DMA2_Stream1_IRQn
#define AUDIO_OUT_SAIx_DMAx_PERIPH_DATA_SIZE     DMA_PDATAALIGN_HALFWORD
#define AUDIO_OUT_SAIx_DMAx_MEM_DATA_SIZE        DMA_MDATAALIGN_HALFWORD
#define AUDIO_OUT_SAIx_DMAx_IRQHandler           DMA2_Stream1_IRQHandler

/*------------------------------------------------------------------------------
                        AUDIO IN defines parameters
------------------------------------------------------------------------------*/
/* SAI peripheral configuration defines */
#define AUDIO_IN_SAIx                           SAI2_Block_B
#define AUDIO_IN_SAIx_CLK_ENABLE()              __HAL_RCC_SAI2_CLK_ENABLE()
#define AUDIO_IN_SAIx_CLK_DISABLE()             __HAL_RCC_SAI2_CLK_DISABLE()
#define AUDIO_IN_SAIx_AF                        GPIO_AF10_SAI2
#define AUDIO_IN_SAIx_SD_ENABLE()               __HAL_RCC_GPIOG_CLK_ENABLE()
#define AUDIO_IN_SAIx_SD_GPIO_PORT              GPIOG
#define AUDIO_IN_SAIx_SD_PIN                    GPIO_PIN_10

/* SAI DMA Stream definitions */
#define AUDIO_IN_SAIx_DMAx_CLK_ENABLE()         __HAL_RCC_DMA2_CLK_ENABLE()
#define AUDIO_IN_SAIx_DMAx_STREAM               DMA2_Stream4
#define AUDIO_IN_SAIx_DMAx_REQUEST              DMA_REQUEST_SAI2_B
#define AUDIO_IN_SAIx_DMAx_IRQ                  DMA2_Stream4_IRQn
#define AUDIO_IN_SAIx_DMAx_PERIPH_DATA_SIZE     DMA_PDATAALIGN_HALFWORD
#define AUDIO_IN_SAIx_DMAx_MEM_DATA_SIZE        DMA_MDATAALIGN_HALFWORD
#define AUDIO_IN_SAIx_DMAx_IRQHandler           DMA2_Stream4_IRQHandler
/* Select the interrupt preemption priority and subpriority for the DMA interrupt */
#define AUDIO_OUT_IRQ_PREPRIO                    ((uint32_t)0x0E)
#define AUDIO_IN_IRQ_PREPRIO                ((uint32_t)0x0F)

#define VOLUME_OUT_CONVERT(Volume)    (((Volume) > 100)? 63:((uint8_t)(((Volume) * 63) / 100)))
#define VOLUME_IN_CONVERT(Volume)     (((Volume) >= 100)? 239:((uint8_t)(((Volume) * 239) / 100)))


#define MY_BUFFER_SIZE_SAMPLES 1024
#define MY_DMA_BYTES_PER_FRAME 8
#define MY_DMA_BYTES_PER_MSIZE 2
#define MY_DMA_BUFFER_SIZE_BYTES MY_BUFFER_SIZE_SAMPLES * MY_DMA_BYTES_PER_FRAME
#define MY_DMA_BUFFER_SIZE_MSIZES MY_DMA_BUFFER_SIZE_BYTES / MY_DMA_BYTES_PER_MSIZE

typedef struct
{
  int32_t (*Init)(void *, void *);
  int32_t (*DeInit)(void *);
  int32_t (*ReadID)(void *, uint32_t *);
  int32_t (*Play)(void *);
  int32_t (*Pause)(void *);
  int32_t (*Resume)(void *);
  int32_t (*Stop)(void *, uint32_t);
  int32_t (*SetFrequency)(void *, uint32_t);
  int32_t (*GetFrequency)(void *);
  int32_t (*SetVolume)(void *, uint32_t, uint8_t);
  int32_t (*GetVolume)(void *, uint32_t, uint8_t *);
  int32_t (*SetMute)(void *, uint32_t);
  int32_t (*SetOutputMode)(void *, uint32_t);
  int32_t (*SetResolution)(void *, uint32_t);
  int32_t (*GetResolution)(void *, uint32_t *);
  int32_t (*SetProtocol)(void *, uint32_t);
  int32_t (*GetProtocol)(void *, uint32_t *);
  int32_t (*Reset)(void *);
} AUDIO_Drv_t;



void fill_buffer_with_square_wave(int16_t * buf, uint32_t num_samples);
void ConvertSampleBufferToDMABuffer(int16_t * sampleBuffer, uint8_t *dmaBuffer, uint32_t num_samples);
HAL_StatusTypeDef My_SAI_ClockConfig(uint32_t AudioFreq);
void My_AUDIO_OUT_MspInit(void);
void My_SAI_Out_Init(uint32_t AudioFreq);
void My_AUDIO_IN_MspInit(void);
void My_SAI_In_Init(uint32_t AudioFreq);
int32_t WM8994_Probe(void);

void LowerHalf_Input_Samples(int16_t * input_samples,uint32_t num_samples);

void UpperHalf_Input_Samples(int16_t * input_samples,uint32_t num_samples);

void LowerHalf_Output_Samples(int16_t * out_samples, uint32_t num_samples);

void UpperHalf_Output_Samples(int16_t * out_samples, uint32_t num_samples);

void audio_init(uint32_t frequency);
void Output_Sample(int16_t sample, int16_t * start, uint32_t pos);
