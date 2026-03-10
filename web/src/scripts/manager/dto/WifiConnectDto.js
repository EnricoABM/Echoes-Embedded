export class WifiConnectDto {
  constructor(ssid, pass, ip, gateway, subnet) {
    this.ssid = ssid;
    this.pass = pass;
    this.ip = ip;
    this.gateway = gateway;
    this.subnet = subnet;
  }
}
