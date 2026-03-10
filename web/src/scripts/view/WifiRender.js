import { WifiForm } from "./WifiForm.js";

export class WifiRender {
  #wifiManager = null;
  #wifiForm = null;
  #networksDiv = null;
  #wifiModal = null;
  #wifiModalName = null;
  #wifiModalSsid = null;
  #wifiModalPassword = null;
  #icons = null;

  constructor(wifiManager) {
    this.#wifiManager = wifiManager;
    this.#wifiForm = new WifiForm(wifiManager);
    this.#networksDiv = document.getElementById('networks');
    this.#wifiModal = document.getElementById('wifi-modal');
    this.#wifiModalName = document.getElementById('wifi-modal-name');
    this.#wifiModalSsid = document.getElementById('wifi-modal-ssid');
    this.#wifiModalPassword = document.getElementById('wifi-modal-password');
  }

  setup() {
    this.#setupIcons()
    this.#wifiForm.setup();
  }

  #setupIcons() {
    const wifiFullIcon = `
      <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="feather feather-wifi"><path d="M5 12.55a11 11 0 0 1 14.08 0"></path><path d="M1.42 9a16 16 0 0 1 21.16 0"></path><path d="M8.53 16.11a6 6 0 0 1 6.95 0"></path><line x1="12" y1="20" x2="12.01" y2="20"></line></svg>
    `;
    const wifi75Icon = `
      <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="feather feather-wifi" style="--darkreader-inline-stroke: currentColor;" data-darkreader-inline-stroke=""><path d="M5 12.55a11 11 0 0 1 14.08 0"></path><path d="M8.53 16.11a6 6 0 0 1 6.95 0"></path><line x1="12" y1="20" x2="12.01" y2="20"></line></svg>
    `;
    const wifi50Icon = `
      <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="feather feather-wifi" style="--darkreader-inline-stroke: currentColor;" data-darkreader-inline-stroke=""><path d="M8.53 16.11a6 6 0 0 1 6.95 0"></path><line x1="12" y1="20" x2="12.01" y2="20"></line></svg>
    `;
    const wifi25Icon = `
      <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="feather feather-wifi" style="--darkreader-inline-stroke: currentColor;" data-darkreader-inline-stroke=""><line x1="12" y1="20" x2="12.01" y2="20"></line></svg>
    `;
    const lockIcon = `
      <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="feather feather-lock"><rect x="3" y="11" width="18" height="11" rx="2" ry="2"></rect><path d="M7 11V7a5 5 0 0 1 10 0v4"></path></svg>
    `;
    const parser = new DOMParser();
    const wifiFullSvg = parser.parseFromString(wifiFullIcon, 'image/svg+xml');
    const wifiFullSvgEl = wifiFullSvg.documentElement;
    const wifi75Svg = parser.parseFromString(wifi75Icon, 'image/svg+xml');
    const wifi75SvgEl = wifi75Svg.documentElement;
    const wifi50Svg = parser.parseFromString(wifi50Icon, 'image/svg+xml');
    const wifi50SvgEl = wifi50Svg.documentElement;
    const wifi25Svg = parser.parseFromString(wifi25Icon, 'image/svg+xml');
    const wifi25SvgEl = wifi25Svg.documentElement;
    const lockSvg = parser.parseFromString(lockIcon, 'image/svg+xml');
    const lockSvgEl = lockSvg.documentElement;
    this.#icons = {
      wifiFull: wifiFullSvgEl,
      wifi75: wifi75SvgEl,
      wifi50: wifi50SvgEl,
      wifi25: wifi25SvgEl,
      lock: lockSvgEl,
    };
  }

  render() {
    this.#networksDiv.innerHTML = '';
    this.#wifiManager.wifis.forEach(wifi => this.renderWifi(wifi));
  }

  renderWifi(wifi) {
    const btn = this.createButton(wifi);

    const div = document.createElement('div');
    if (wifi.rssi >= -55)
      div.appendChild(this.#icons.wifiFull.cloneNode(true));
    else if (wifi.rssi > -65 && wifi.rssi < -55)
      div.appendChild(this.#icons.wifi75.cloneNode(true));
    else if (wifi.rssi > -75 && wifi.rssi < -65)
      div.appendChild(this.#icons.wifi50.cloneNode(true));
    else
      div.appendChild(this.#icons.wifi25.cloneNode(true));

    const subDiv = document.createElement('div');
    subDiv.classList.add('network-status');

    const nameSpan = this.createNameSpan(wifi.ssid);
    const statusSpan = this.createStatusSpan(wifi.status);

    subDiv.appendChild(nameSpan);
    subDiv.appendChild(statusSpan);

    div.appendChild(subDiv);
    
    btn.appendChild(div);
    if (wifi.secure)
      btn.appendChild(this.#icons.lock.cloneNode(true));

    this.#networksDiv.appendChild(btn);
  }

  createButton(wifi) {
    const btn = document.createElement('button');
    btn.classList.add('network-option');
    btn.addEventListener('click', () => this.selectWifi(wifi));
    return btn;
  }

  createNameSpan(ssid) {
    const nameSpan = document.createElement('span');
    nameSpan.classList.add('network-name');
    if (ssid === '') {
      nameSpan.textContent = 'Rede oculta';
    } else {
      nameSpan.textContent = ssid;
    }
    return nameSpan;
  }

  createStatusSpan(status) {
    const statusSpan = document.createElement('span');
    switch (status) {
      case 0:
        statusSpan.innerHTML = '&nbsp;';
        break;
      case 1:
        statusSpan.textContent = 'Conectando';
        break;
      case 2:
        statusSpan.textContent = 'Conectado';
        break;
      case 3:
        statusSpan.textContent = 'Erro ao conectar';
        break;
    }
    return statusSpan;
  }

  selectWifi(wifi) {
    this.#wifiModalSsid.type = 'hidden';
    this.#wifiModal.style.display = 'flex';
    this.#wifiModalName.textContent = wifi.ssid;
    this.#wifiModalSsid.value = wifi.ssid;
    if (wifi.ssid === '') {
      this.#wifiModalName.textContent = 'Rede oculta';
      this.#wifiModalSsid.type = 'text';
    }
    if (wifi.secure) {
      this.#wifiModalPassword.style.display = 'flex';
    } else {
      this.#wifiModalPassword.style.display = 'none';
    }
  }
}
