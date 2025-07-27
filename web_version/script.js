// script.js

const API = {
  STATUS: '/status',
  BUZZER: '/buzzer'
};

const elems = {
  moistureValue: document.getElementById('moisture-value'),
  pumpStatus:    document.getElementById('pump-status'),
  lastUpdated:   document.getElementById('last-updated'),
  refreshBtn:    document.getElementById('refresh-btn'),
  toggleBtn:     document.getElementById('manual-toggle'),
};

// Fetch current status from ESP
async function fetchStatus() {
  try {
    const res = await fetch(API.STATUS);
    if (!res.ok) throw new Error(`HTTP ${res.status}`);
    const data = await res.json();
    updateUI(data);
  } catch (err) {
    console.error('Failed to fetch status:', err);
  }
}

// Send toggle command to ESP
async function togglePump() {
  const isOn = elems.pumpStatus.textContent === 'ON';
  try {
    const res = await fetch(API.BUZZER, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ on: !isOn })
    });
    if (!res.ok) throw new Error(`HTTP ${res.status}`);
    const json = await res.json();
    if (json.result === 'ok') {
      // reflect new state
      elems.pumpStatus.textContent = isOn ? 'OFF' : 'ON';
      elems.pumpStatus.classList.toggle('on', !isOn);
      elems.toggleBtn.textContent = isOn ? 'Start Pump' : 'Stop Pump';
    }
  } catch (err) {
    console.error('Toggle pump failed:', err);
  }
}

// Update DOM elements
function updateUI({ smoke_raw, alert }) {
  // Convert raw ADC to percentage (0-100 wet->dry)
  const pct = Math.round((1 - (smoke_raw / 4095)) * 100);
  elems.moistureValue.textContent = `${pct}%`;
  const pumpOn = alert === true;
  elems.pumpStatus.textContent = pumpOn ? 'ON' : 'OFF';
  elems.pumpStatus.classList.toggle('on', pumpOn);
  elems.toggleBtn.textContent = pumpOn ? 'Stop Pump' : 'Start Pump';
  const now = new Date();
  elems.lastUpdated.textContent = now.toLocaleTimeString();
}

// Event listeners
elems.refreshBtn.addEventListener('click', fetchStatus);
elems.toggleBtn.addEventListener('click', togglePump);

// Auto-refresh every 5 seconds
setInterval(fetchStatus, 5000);

// Initial fetch
fetchStatus();
