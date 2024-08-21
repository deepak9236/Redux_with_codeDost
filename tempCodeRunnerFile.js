function initCounter() {
    let count = 0;
    return function () {
        count++;
    };
}

// Dublicate count bana sakte by use of closer
console.log(initCounter()); // [Function (anonymous)]
let counter = initCounter();
console.log(counter()); // 0
counter() // 1

let counter1 = initCounter(); // alag counter ki tarh behave kare ga
console.log(counter1());  // 0
console.log(counter1()); // 1