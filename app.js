var Module={onRuntimeInitialized:function(){route()}};
const $=s=>document.querySelector(s);
const C=(f,t=[],a=[])=>JSON.parse(Module.ccall(f,'string',t,a));
let cur=null;
function route(){const h=(location.hash||'#home').slice(1);
 document.querySelectorAll('section').forEach(s=>s.hidden=s.id!==h);
 document.querySelectorAll('nav a').forEach(a=>a.classList.toggle('on',a.hash==='#'+h));
 if(Module.ccall){if(h==='dsa')dsa();if(h==='intake')qv();}}
addEventListener('hashchange',route);addEventListener('DOMContentLoaded',route);
function qv(){const s=C('api_state');$('#qv').innerHTML=s.queue.map(i=>`<span>#${i}</span>`).join('')||'<small>Nobody waiting.</small>';}
function reg(){const r=C('api_register',['string','number','string','string'],[$('#n').value,+$('#a').value,$('#p').value,$('#c').value]);
 $('#rmsg').textContent=r.ok?`Registered as patient #${r.id}. ${r.queued} waiting.`:r.msg;qv();}
function nxt(){const r=C('api_next');$('#cmsg').textContent=r.ok?'':r.msg;if(!r.ok)return;cur=r;
 $('#pt').textContent=`#${r.id} ${r.name}, ${r.age} y, ${r.prakriti}. Complaint: ${r.cc}`;
 const s=C('api_suggest',['string'],[r.cc]);
 $('#sug').innerHTML=s.matches.map(m=>`<label><input type="radio" name="t" value="${m.term}"> <b>${m.term}</b> <small>${m.system}: ${m.namc} to ${m.tm2}</small></label>`).join('')||'<small>No suggestion. Type a term below.</small>';$('#care').innerHTML='';}
function careHtml(t,p){const c=C('api_care',['string','string'],[t,p||'']);if(!c.ok)return c.msg;
 return `<div class="card"><b>${c.term}</b><br>Aushadhi: ${c.aushadhi}<br>Sevana kala: ${c.kala}<br>Pathya: ${c.pathya}<br>Apathya: ${c.apathya}<br><small>${c.prakriti} Doses are set by the physician.</small></div>`;}
function fin(){if(!cur)return;const t=($('#man').value||(document.querySelector('input[name=t]:checked')||{}).value||'').trim();
 const r=C('api_finalize',['number','string'],[cur.id,t]);if(!r.ok){$('#cmsg').textContent=r.msg;return}
 $('#cmsg').textContent=`Saved. NAMASTE ${r.namc} / ICD-11 TM2 ${r.tm2}`;$('#care').innerHTML=careHtml(t,cur.prakriti);}
function und(){const r=C('api_undo');$('#cmsg').textContent=r.ok?'Last diagnosis removed.':r.msg;}
function srch(){const s=C('api_suggest',['string'],[$('#mq').value]);
 $('#mr').innerHTML=s.matches.length?'<table><tr><th>Term</th><th>System</th><th>NAMASTE</th><th>ICD-11 TM2</th></tr>'+s.matches.map(m=>`<tr><td>${m.term}</td><td>${m.system}</td><td>${m.namc}</td><td>${m.tm2}</td></tr>`).join('')+'</table>'+s.matches.map(m=>careHtml(m.term,'')).join(''):'<p>No match. Try a symptom such as cough or fever.</p>';}
function bil(){const r=C('api_bill',['number'],[+$('#bid').value]);
 $('#br').innerHTML=r.ok?`<div class="card">${r.name}, ${r.age} y (patient #${r.id})</div><table><tr><th>Diagnosis</th><th>NAMASTE</th><th>ICD-11 TM2</th></tr>`+r.visits.map(v=>`<tr><td>${v.term}</td><td>${v.namc}</td><td>${v.tm2}</td></tr>`).join('')+`</table><small>${r.note}</small>`:r.msg;}
function dsa(){const s=C('api_state');
 $('#dv').innerHTML=`<h3>Queue (front to back)</h3><div class="q">${s.queue.map(i=>`<span>#${i}</span>`).join('')||'<small>empty</small>'}</div>
 <h3>BST in-order (sorted by ID)</h3><div class="t">${s.tree.map(t=>`<span>${t.id} ${t.name}</span>`).join('')||'<small>empty</small>'}</div>
 <h3>Undo stack depth</h3><p>${s.stack}</p><h3>Hash buckets (chain lengths)</h3><div class="t">${s.buckets.map((b,i)=>`<span>${i}: ${b}</span>`).join('')}</div>
 <table><tr><th>Operation</th><th>Time</th></tr><tr><td>Queue push / pop</td><td>O(1)</td></tr><tr><td>BST insert / find</td><td>O(log n) average</td></tr><tr><td>Hash lookup</td><td>O(1) average</td></tr><tr><td>List append</td><td>O(k) for k visits</td></tr><tr><td>Stack push / pop</td><td>O(1)</td></tr></table>`;}
