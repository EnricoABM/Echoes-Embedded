import { WifiRender } from "./view/WifiRender.js";
import { WifiManager } from "./manager/WifiManager.js";

document.addEventListener('DOMContentLoaded', () => {
const wifiManager = new WifiManager();
const wifiRender = new WifiRender(wifiManager);

wifiManager.addListener('fetch', () => wifiRender.render());
wifiManager.addListener('add', () => wifiRender.render());
wifiManager.addListener('update', () => wifiRender.render());
wifiManager.setup();
wifiRender.setup();

})
