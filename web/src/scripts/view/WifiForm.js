import { Debouncer } from "../util/Debouncer.js";
import { WifiConnectDto } from "../manager/dto/WifiConnectDto.js";

export class WifiForm {
  #wifiManager = null;
  #wifiIpDebouncer = null;
  #wifiModal = null;
  #wifiModalCancel = null;
  #wifiConnect = null;
  #wifiSubnet = null;
  #wifiError = null;
  #wifiGateway = null;

  constructor(wifiManager) {
    this.#wifiManager = wifiManager;
    this.#wifiModal = document.getElementById('wifi-modal');
    this.#wifiModalCancel = document.getElementById('wifi-modal-cancel');
    this.#wifiConnect = document.getElementById('wifi-connect');
    this.#wifiSubnet = document.querySelector('input[name=subnet]');
    this.#wifiError = document.getElementById('wifi-error');
    this.#wifiGateway = document.querySelector('input[name=gateway]');
  }

  setup() {
    this.#setupDebouncer();
    this.#setupClickListeners();
    this.#setupConnectRequest();
  }

  #setupDebouncer() {
    this.#wifiIpDebouncer = new Debouncer('input[name=ip]', 'input');
    this.#wifiIpDebouncer.addCallback((ev) => {
      this.#setGatewayFromIp(ev.target.value);
    })
  }

  #setGatewayFromIp(ip) {
    const isValid = this.#isValidIPv4(ip);
    if (!isValid)
      return;

    const numbers = ip.split('.');
    numbers[3] = '1';
    
    this.#wifiGateway.value = numbers.join('.');
  }

  #isValidIPv4(ip) {
    const regex = /^(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)(\.(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)){3}$/;
    return regex.test(ip);
  }

  #setupClickListeners() {
    this.#wifiModal.addEventListener('click', ev => {
      if (ev.target !== this.#wifiModal)
        return;
      this.#wifiModal.style.display = 'none';
      this.#resetForm();
    })
    this.#wifiModalCancel.addEventListener('click', () => {
      this.#wifiModal.style.display = 'none';
      this.#resetForm();
    })
  }

  #resetForm() {
    this.#wifiConnect.reset();
    this.#wifiSubnet.value = '255.255.255.0';
  }

  #setupConnectRequest() {
    this.#wifiConnect.addEventListener('submit', ev => {
      ev.preventDefault();
      this.#requestWifiConnection();
    })
  }

  async #requestWifiConnection() {
    try {
      await this.#_requestWifiConnection();
    } catch(err) {
      this.#wifiError.textContent = err.message;
    }
  }

  async #_requestWifiConnection() {
    const formData = new FormData(this.#wifiConnect);
    const ssid = formData.get('ssid');
    const pass = formData.get('password');
    const ip = formData.get('ip');
    const gateway = formData.get('gateway');
    const subnet = formData.get('subnet');

    if (ip)
      this.#validateAdvanced(ip, gateway, subnet);

    this.#wifiModal.style.display = 'none';
    this.#resetForm();
    const wifiConnectDto = new WifiConnectDto(ssid, pass, ip, gateway, subnet);
    await this.#wifiManager.connectToWifi(wifiConnectDto);
  }

  #validateAdvanced(ip, gateway, subnet) {
    if (!this.#isValidIPv4(ip))
      throw new Error('Digite um ip válido');
    if (!this.#isValidIPv4(gateway))
      throw new Error('Digite um gateway válido');
    if (!this.#isValidIPv4(subnet))
      throw new Error('Digite uma máscara válida');
  }
}
