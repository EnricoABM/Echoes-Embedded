export class Debouncer {
  #input = null;
  #timer = null;
  #callbacks = [];
  #interval = 500;

  constructor(selector, event) {
    this.#input = document.querySelector(selector);
    if (this.#input)
      this.#input.addEventListener(event, ev => this.#debounce(ev));
  }

  addCallback(cb) {
    this.#callbacks.push(cb);
  }

  removeCallback(cb) {
    const i = this.#callbacks.indexOf(cb);
    if (i !== -1)
      this.#callbacks.splice(i, 1);
  }

  #debounce(ev) {
    clearTimeout(this.#timer);
    this.#timer = setTimeout(() => {
      this.#notify(ev);
    }, this.#interval);
  }

  #notify(ev) {
    for (const cb of this.#callbacks) {
      cb(ev);
    }
  }
}
