---
cssclasses:
---

```dataviewjs
const PPH = 52;   // hauteur d'une heure en pixels
let offset = 0;   // 0 = semaine en cours
const ics = app.plugins.getPlugin("ics");

dv.container.createEl("style", { text: `
.edt-large .markdown-preview-sizer, .edt-large .cm-sizer { max-width: none !important; }
.edt-wrap { overflow-x: auto; }
.edt-nav { display: flex; gap: 6px; align-items: center; margin-bottom: 8px; flex-wrap: wrap; }
.edt-nav button { padding: 2px 12px; cursor: pointer; }
.edt-titre { font-weight: 600; margin-left: 8px; }
.edt-grid { display: grid; min-width: 640px; border: 1px solid var(--background-modifier-border); border-radius: 8px; overflow: hidden; font-size: 12px; }
.edt-corner, .edt-dayhead { background: var(--background-secondary); border-bottom: 1px solid var(--background-modifier-border); padding: 4px; text-align: center; }
.edt-dayhead { border-left: 1px solid var(--background-modifier-border); text-transform: capitalize; font-weight: 600; }
.edt-dayhead.today { color: var(--interactive-accent); }
.edt-date { font-weight: 400; color: var(--text-muted); font-size: 11px; }
.edt-allday { margin-top: 3px; background: var(--interactive-accent); color: var(--text-on-accent); border-radius: 4px; font-size: 11px; padding: 1px 4px; }
.edt-times { position: relative; }
.edt-hour { position: absolute; right: 4px; transform: translateY(-6px); color: var(--text-faint); font-size: 10px; }
.edt-hour:first-child { transform: none; }
.edt-col { position: relative; border-left: 1px solid var(--background-modifier-border); background-image: linear-gradient(to bottom, var(--background-modifier-border) 1px, transparent 1px); }
.edt-col.today { background-color: color-mix(in srgb, var(--interactive-accent) 6%, transparent); }
.edt-ev { position: absolute; box-sizing: border-box; border-radius: 6px; padding: 3px 5px; overflow: hidden; line-height: 1.25;
  background: color-mix(in srgb, var(--c) 22%, var(--background-primary)); border-left: 3px solid var(--c); }
.edt-h, .edt-l { font-size: 10px; color: var(--text-muted); }
.edt-t { font-weight: 600; word-break: break-word; }
.edt-now { position: absolute; left: 0; right: 0; height: 2px; background: var(--color-red); z-index: 2; }
.edt-msg { padding: 12px; color: var(--text-muted); }
`});
const wrap = dv.container.createDiv({ cls: "edt-wrap" });

// même matière = même couleur (on colore d'après le début du titre)
const couleur = s => { let h = 0; for (const c of (s || "").split(/\s[-–:]\s|\(/)[0]) h = (h * 31 + c.charCodeAt(0)) % 360; return `hsl(${h} 65% 55%)`; };
const heure = m => m.hours() + m.minutes() / 60;

async function render() {
  wrap.empty();
  const lundi = moment().startOf("isoWeek").add(offset, "weeks");
  const days = [...Array(6).keys()].map(i => lundi.clone().add(i, "days"));
  const fr = m => m.clone().locale("fr");

  const nav = wrap.createDiv({ cls: "edt-nav" });
  nav.createEl("button", { text: "◀" }).onclick = () => { offset--; render(); };
  nav.createEl("button", { text: "Cette semaine" }).onclick = () => { offset = 0; render(); };
  nav.createEl("button", { text: "▶" }).onclick = () => { offset++; render(); };
  nav.createSpan({ cls: "edt-titre", text: `Semaine ${lundi.format("WW")} · du ${fr(lundi).format("D MMM")} au ${fr(days[5]).format("D MMM YYYY")}` });

  if (!ics) { wrap.createDiv({ cls: "edt-msg", text: "⚠️ Active le plugin ICS (Paramètres → Plugins communautaires)." }); return; }
  const msg = wrap.createDiv({ cls: "edt-msg", text: "Chargement de l'EDT…" });
  let evts = [];
  try { evts = await ics.getEvents(...days); }
  catch (err) { msg.setText("⚠️ EDT indisponible : " + err.message); return; }
  msg.remove();

  const cours = days.map(() => []), journee = days.map(() => []);
  for (const e of evts) {
    const s = moment(e.startDateTime), f = moment(e.endDateTime);
    const i = days.findIndex(d => d.isSame(s, "day"));
    if (i < 0) continue;
    if (e.allDay) journee[i].push(e);
    else cours[i].push({ e, s, f, h0: heure(s), h1: f.isSame(s, "day") ? heure(f) : 24 });
  }
  const nbJours = (cours[5].length || journee[5].length) ? 6 : 5;
  const tous = cours.flat();
  const hMin = Math.min(8, ...tous.map(x => Math.floor(x.h0)));
  const hMax = Math.max(18, ...tous.map(x => Math.ceil(x.h1)));
  const H = (hMax - hMin) * PPH;

  const grid = wrap.createDiv({ cls: "edt-grid" });
  grid.style.gridTemplateColumns = `44px repeat(${nbJours}, minmax(0, 1fr))`;
  grid.createDiv({ cls: "edt-corner" });
  for (let i = 0; i < nbJours; i++) {
    const h = grid.createDiv({ cls: "edt-dayhead" + (days[i].isSame(moment(), "day") ? " today" : "") });
    h.createDiv({ text: fr(days[i]).format("dddd") });
    h.createDiv({ cls: "edt-date", text: days[i].format("DD/MM") });
    for (const e of journee[i]) h.createDiv({ cls: "edt-allday", text: e.summary });
  }
  const tc = grid.createDiv({ cls: "edt-times" });
  tc.style.height = H + "px";
  for (let h = hMin; h < hMax; h++) tc.createDiv({ cls: "edt-hour", text: `${h}h` }).style.top = (h - hMin) * PPH + "px";

  for (let i = 0; i < nbJours; i++) {
    const today = days[i].isSame(moment(), "day");
    const col = grid.createDiv({ cls: "edt-col" + (today ? " today" : "") });
    col.style.height = H + "px";
    col.style.backgroundSize = `100% ${PPH}px`;

    // cours qui se chevauchent → côte à côte
    const list = cours[i].sort((a, b) => a.h0 - b.h0 || b.h1 - a.h1);
    let groupe = [], fin = -1;
    const ranger = () => {
      const voies = [];
      for (const x of groupe) { let v = voies.findIndex(t => t <= x.h0); if (v < 0) { v = voies.length; voies.push(0); } voies[v] = x.h1; x.voie = v; }
      for (const x of groupe) x.nb = voies.length;
      groupe = [];
    };
    for (const x of list) { if (groupe.length && x.h0 >= fin) { ranger(); fin = -1; } groupe.push(x); fin = Math.max(fin, x.h1); }
    if (groupe.length) ranger();

    for (const x of list) {
      const c = col.createDiv({ cls: "edt-ev" });
      c.style.top = (x.h0 - hMin) * PPH + 1 + "px";
      c.style.height = Math.max(18, (x.h1 - x.h0) * PPH - 2) + "px";
      c.style.left = `calc(${x.voie * 100 / x.nb}% + 2px)`;
      c.style.width = `calc(${100 / x.nb}% - 4px)`;
      c.style.setProperty("--c", couleur(x.e.summary));
      const horaire = `${x.s.format("HH:mm")}–${x.f.format("HH:mm")}`;
      c.createDiv({ cls: "edt-h", text: horaire });
      c.createDiv({ cls: "edt-t", text: x.e.summary });
      if (x.e.location) c.createDiv({ cls: "edt-l", text: "📍 " + x.e.location });
      c.title = [x.e.summary, horaire, x.e.location, x.e.description].filter(Boolean).join("\n");
    }
    if (today) {
      const hn = heure(moment());
      if (hn >= hMin && hn <= hMax) col.createDiv({ cls: "edt-now" }).style.top = (hn - hMin) * PPH + "px";
    }
  }
  if (!tous.length && !journee.flat().length) wrap.createDiv({ cls: "edt-msg", text: "Aucun cours à l'école cette semaine (semaine entreprise ?)." });
}
render();
```

