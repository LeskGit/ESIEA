---
cssclasses:
  - pp-large
---
```dataviewjs
// Planning perso : clique sur un créneau vide pour ajouter, sur un événement pour le modifier / supprimer.
// Les données sont stockées dans planning-perso.json (même dossier que cette note).
const dossier = dv.current().file.folder;
const FICHIER = (dossier ? dossier + "/" : "") + "planning-perso.json";
const PPH = 48;
const TYPES = { "Séance": "#3b82f6", "Contrôle": "#ef4444", "Devoir": "#f59e0b", "Révision": "#22c55e", "Projet": "#a855f7", "Autre": "#64748b" };
const adapter = app.vault.adapter;
let data = { events: [] };
let offset = 0;

dv.container.createEl("style", { text: `
.pp-large .markdown-preview-sizer, .pp-large .cm-sizer { max-width: none !important; }
.pp { overflow-x: auto; }
.pp-nav { display: flex; gap: 6px; align-items: center; flex-wrap: wrap; margin-bottom: 8px; }
.pp-nav button, .pp-form button { cursor: pointer; padding: 2px 12px; }
.pp-titre { font-weight: 600; margin: 0 8px; }
.pp-legende { display: flex; gap: 10px; flex-wrap: wrap; font-size: 11px; color: var(--text-muted); margin-bottom: 8px; }
.pp-legende span::before { content: ""; display: inline-block; width: 9px; height: 9px; border-radius: 2px; margin-right: 4px; background: var(--c); }
.pp-form { display: none; border: 1px solid var(--background-modifier-border); border-radius: 8px; padding: 10px; margin-bottom: 10px; background: var(--background-secondary); }
.pp-champs { display: grid; grid-template-columns: repeat(auto-fill, minmax(150px, 1fr)); gap: 8px; }
.pp-champs label { display: flex; flex-direction: column; font-size: 11px; color: var(--text-muted); gap: 2px; }
.pp-champs label.pp-large-champ { grid-column: 1 / -1; }
.pp-champs label.pp-check { flex-direction: row; align-items: center; gap: 6px; }
.pp-champs input, .pp-champs select, .pp-champs textarea { font-size: 13px; }
.pp-actions { display: flex; gap: 6px; margin-top: 10px; flex-wrap: wrap; }
.pp-danger { color: var(--text-error); }
.pp-erreur { color: var(--text-error); font-size: 12px; margin-top: 6px; }
.pp-grid { display: grid; min-width: 700px; border: 1px solid var(--background-modifier-border); border-radius: 8px; overflow: hidden; font-size: 12px; user-select: none; }
.pp-corner, .pp-jour { background: var(--background-secondary); border-bottom: 1px solid var(--background-modifier-border); padding: 4px; text-align: center; }
.pp-jour { border-left: 1px solid var(--background-modifier-border); text-transform: capitalize; font-weight: 600; }
.pp-jour.today { color: var(--interactive-accent); }
.pp-date { font-weight: 400; color: var(--text-muted); font-size: 11px; }
.pp-heures { position: relative; }
.pp-heure { position: absolute; right: 4px; transform: translateY(-6px); color: var(--text-faint); font-size: 10px; }
.pp-heure:first-child { transform: none; }
.pp-col { position: relative; cursor: copy; border-left: 1px solid var(--background-modifier-border);
  background-image: linear-gradient(to bottom, var(--background-modifier-border) 1px, transparent 1px); }
.pp-col:hover { background-color: color-mix(in srgb, var(--interactive-accent) 4%, transparent); }
.pp-col.today { background-color: color-mix(in srgb, var(--interactive-accent) 7%, transparent); }
.pp-ev { position: absolute; box-sizing: border-box; border-radius: 6px; padding: 3px 5px; overflow: hidden; line-height: 1.25; cursor: pointer;
  background: color-mix(in srgb, var(--c) 22%, var(--background-primary)); border-left: 3px solid var(--c); }
.pp-ev:hover { filter: brightness(1.08); box-shadow: 0 1px 4px rgba(0,0,0,.2); }
.pp-h { font-size: 10px; color: var(--text-muted); }
.pp-t { font-weight: 600; word-break: break-word; }
.pp-now { position: absolute; left: 0; right: 0; height: 2px; background: var(--color-red); z-index: 2; pointer-events: none; }
.pp-prochains { margin-top: 14px; }
.pp-prochains h4 { margin: 0 0 6px; }
`});

const wrap = dv.container.createDiv({ cls: "pp" });
// évite que l'éditeur (aperçu en direct) capte les clics / la frappe
for (const evt of ["mousedown", "keydown", "keyup", "keypress"]) wrap.addEventListener(evt, e => e.stopPropagation());

const toH = s => { const [h, m] = (s || "0:0").split(":").map(Number); return h + m / 60; };
const hh = h => `${String(Math.floor(h)).padStart(2, "0")}:${h % 1 ? "30" : "00"}`;
const fr = m => m.clone().locale("fr");
const id = () => Date.now().toString(36) + Math.random().toString(36).slice(2, 6);

async function charger() {
  try { if (await adapter.exists(FICHIER)) data = JSON.parse(await adapter.read(FICHIER)); } catch (e) { data = { events: [] }; }
  data.events ??= [];
}
const sauver = () => adapter.write(FICHIER, JSON.stringify(data, null, 2));

function occurrences(days) {
  const res = days.map(() => []);
  for (const ev of data.events) {
    const d0 = moment(ev.date, "YYYY-MM-DD");
    days.forEach((d, i) => {
      const k = d.format("YYYY-MM-DD");
      const ok = ev.repeat === "weekly"
        ? !d.isBefore(d0, "day") && d.isoWeekday() === d0.isoWeekday() && (!ev.until || k <= ev.until) && !(ev.skip || []).includes(k)
        : ev.date === k;
      if (ok) res[i].push({ ev, date: k, h0: toH(ev.start), h1: toH(ev.end) });
    });
  }
  return res;
}

// ---------- formulaire ----------
let form;
function champ(parent, label, el, cls) {
  const l = parent.createEl("label", { cls });
  if (cls !== "pp-check") l.createSpan({ text: label });
  l.appendChild(el);
  if (cls === "pp-check") l.createSpan({ text: label });
  return el;
}
function input(type, value) { const i = createEl("input", { attr: { type } }); if (type === "checkbox") i.checked = !!value; else i.value = value ?? ""; return i; }

function ouvrirForm(ev, dateOcc, h = 9) {
  form.empty();
  form.style.display = "block";
  form.createEl("strong", { text: ev ? "Modifier l'événement" : "Nouvel événement" });
  const g = form.createDiv({ cls: "pp-champs" });
  const titre = champ(g, "Titre", input("text", ev?.titre), "pp-large-champ");
  titre.placeholder = "ex : Contrôle de Probas, Séance TP Java…";
  const type = champ(g, "Type", createEl("select"));
  for (const t of Object.keys(TYPES)) type.createEl("option", { text: t, value: t });
  type.value = ev?.type ?? "Séance";
  const date = champ(g, "Date", input("date", ev?.date ?? dateOcc));
  const debut = champ(g, "Début", input("time", ev?.start ?? hh(h)));
  const fin = champ(g, "Fin", input("time", ev?.end ?? hh(Math.min(h + 1, 23.5))));
  const repet = champ(g, "Chaque semaine", input("checkbox", ev?.repeat === "weekly"), "pp-check");
  const jusqu = champ(g, "Jusqu'au (optionnel)", input("date", ev?.until));
  const note = champ(g, "Note", createEl("textarea"), "pp-large-champ");
  note.value = ev?.note ?? ""; note.rows = 2;
  const err = form.createDiv({ cls: "pp-erreur" });

  const act = form.createDiv({ cls: "pp-actions" });
  act.createEl("button", { text: ev ? "💾 Enregistrer" : "➕ Ajouter", cls: "mod-cta" }).onclick = async () => {
    const v = { titre: titre.value.trim(), type: type.value, date: date.value, start: debut.value, end: fin.value,
                repeat: repet.checked ? "weekly" : false, until: repet.checked ? jusqu.value : "", note: note.value.trim() };
    if (!v.titre) return err.setText("Donne un titre à l'événement.");
    if (!v.date || !v.start || !v.end) return err.setText("Date, début et fin sont obligatoires.");
    if (toH(v.end) <= toH(v.start)) return err.setText("L'heure de fin doit être après le début.");
    if (ev) Object.assign(ev, v); else data.events.push({ id: id(), skip: [], ...v });
    await sauver(); fermer(); render();
  };
  act.createEl("button", { text: "Annuler" }).onclick = fermer;

  const bouton = (texte, action) => {
    const b = act.createEl("button", { text: texte, cls: "pp-danger" });
    b.onclick = async () => { if (!b.dataset.ok) { b.dataset.ok = 1; b.setText("Confirmer ?"); return; } await action(); await sauver(); fermer(); render(); };
  };
  if (ev && ev.repeat === "weekly") {
    bouton("🗑️ Supprimer cette fois", async () => { (ev.skip ??= []).push(dateOcc); });
    bouton("🗑️ Supprimer la série", async () => { data.events = data.events.filter(e => e !== ev); });
  } else if (ev) {
    bouton("🗑️ Supprimer", async () => { data.events = data.events.filter(e => e !== ev); });
  }
  form.scrollIntoView({ block: "nearest", behavior: "smooth" });
  titre.focus();
}
function fermer() { form.empty(); form.style.display = "none"; }

// ---------- rendu ----------
async function render() {
  wrap.empty();
  const lundi = moment().startOf("isoWeek").add(offset, "weeks");
  const days = [...Array(7).keys()].map(i => lundi.clone().add(i, "days"));

  const nav = wrap.createDiv({ cls: "pp-nav" });
  nav.createEl("button", { text: "◀" }).onclick = () => { offset--; render(); };
  nav.createEl("button", { text: "Cette semaine" }).onclick = () => { offset = 0; render(); };
  nav.createEl("button", { text: "▶" }).onclick = () => { offset++; render(); };
  nav.createSpan({ cls: "pp-titre", text: `Semaine ${lundi.format("WW")} · du ${fr(lundi).format("D MMM")} au ${fr(days[6]).format("D MMM YYYY")}` });
  nav.createEl("button", { text: "＋ Ajouter", cls: "mod-cta" }).onclick = () => ouvrirForm(null, (offset ? lundi : moment()).format("YYYY-MM-DD"));

  const leg = wrap.createDiv({ cls: "pp-legende" });
  for (const [t, c] of Object.entries(TYPES)) leg.createSpan({ text: t }).style.setProperty("--c", c);

  form = wrap.createDiv({ cls: "pp-form" });

  const occ = occurrences(days);
  const tous = occ.flat();
  const hMin = Math.min(8, ...tous.map(x => Math.floor(x.h0)));
  const hMax = Math.max(20, ...tous.map(x => Math.ceil(x.h1)));
  const H = (hMax - hMin) * PPH;

  const grid = wrap.createDiv({ cls: "pp-grid" });
  grid.style.gridTemplateColumns = "44px repeat(7, minmax(0, 1fr))";
  grid.createDiv({ cls: "pp-corner" });
  days.forEach(d => {
    const h = grid.createDiv({ cls: "pp-jour" + (d.isSame(moment(), "day") ? " today" : "") });
    h.createDiv({ text: fr(d).format("dddd") });
    h.createDiv({ cls: "pp-date", text: d.format("DD/MM") });
  });
  const tc = grid.createDiv({ cls: "pp-heures" });
  tc.style.height = H + "px";
  for (let h = hMin; h < hMax; h++) tc.createDiv({ cls: "pp-heure", text: `${h}h` }).style.top = (h - hMin) * PPH + "px";

  days.forEach((d, i) => {
    const k = d.format("YYYY-MM-DD");
    const today = d.isSame(moment(), "day");
    const col = grid.createDiv({ cls: "pp-col" + (today ? " today" : "") });
    col.style.height = H + "px";
    col.style.backgroundSize = `100% ${PPH}px`;
    col.title = "Clique pour ajouter un événement";
    col.onclick = e => {
      if (e.target !== col) return;
      const h = hMin + Math.floor((e.offsetY / PPH) * 2) / 2;
      ouvrirForm(null, k, Math.min(h, 23));
    };

    // événements qui se chevauchent → côte à côte
    const list = occ[i].sort((a, b) => a.h0 - b.h0 || b.h1 - a.h1);
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
      const c = col.createDiv({ cls: "pp-ev" });
      c.style.top = (x.h0 - hMin) * PPH + 1 + "px";
      c.style.height = Math.max(18, (x.h1 - x.h0) * PPH - 2) + "px";
      c.style.left = `calc(${x.voie * 100 / x.nb}% + 2px)`;
      c.style.width = `calc(${100 / x.nb}% - 4px)`;
      c.style.setProperty("--c", TYPES[x.ev.type] ?? TYPES.Autre);
      c.createDiv({ cls: "pp-h", text: `${x.ev.start}–${x.ev.end} · ${x.ev.type}${x.ev.repeat ? " 🔁" : ""}` });
      c.createDiv({ cls: "pp-t", text: x.ev.titre });
      c.title = [x.ev.titre, `${x.ev.type} · ${x.ev.start}–${x.ev.end}`, x.ev.note].filter(Boolean).join("\n");
      c.onclick = e => { e.stopPropagation(); ouvrirForm(x.ev, x.date); };
    }
    if (today) {
      const hn = moment().hours() + moment().minutes() / 60;
      if (hn >= hMin && hn <= hMax) col.createDiv({ cls: "pp-now" }).style.top = (hn - hMin) * PPH + "px";
    }
  });

  // prochains contrôles (60 jours)
  const futur = [...Array(60).keys()].map(i => moment().startOf("day").add(i, "days"));
  const ctrl = occurrences(futur).flat().filter(x => x.ev.type === "Contrôle").sort((a, b) => a.date.localeCompare(b.date) || a.h0 - b.h0);
  const p = wrap.createDiv({ cls: "pp-prochains" });
  p.createEl("h4", { text: "🔴 Prochains contrôles" });
  if (!ctrl.length) p.createDiv({ cls: "pp-date", text: "Aucun contrôle prévu dans les 60 prochains jours." });
  else {
    const ul = p.createEl("ul");
    for (const x of ctrl) {
      const j = moment(x.date).diff(moment().startOf("day"), "days");
      ul.createEl("li", { text: `${fr(moment(x.date)).format("ddd D MMM")} · ${x.ev.start} — ${x.ev.titre} (${j === 0 ? "aujourd'hui" : "J-" + j})` });
    }
  }
}

await charger();
await render();
```
