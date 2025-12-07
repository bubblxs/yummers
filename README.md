<h2 align="center">yummers</h2>

> your nodejs application is not using enough RAM? say less.

## usage

commonjs:

```js
const Yummers = require("#lib-cjs");
const y = new Yummers(2 ** 16);

y.feed();
console.log(y.memsize()) // => 65536

y.feed();
console.log(y.memsize()) // => 131072

y.refeed(2 ** 8);
console.log(y.memsize()) // => 256

y.flush();
console.log(y.memsize()) // => 0
```

es6:

```js
import Yummers from "#lib-es6";

const y = new Yummers(2 ** 16);

y.feed();
console.log(y.memsize()) // => 65536

y.feed();
console.log(y.memsize()) // => 131072

y.refeed(2 ** 8);
console.log(y.memsize()) // => 256

y.flush();
console.log(y.memsize()) // => 0
```

you can also install via npm:

``` npm install @bubblxs/yummers@1.0.0 ```

```js
import Yummers from "@bubblxs/yummers"

/* ... */
```

## class methods

```js

/**
* creates an instance of Yummers with a specified memory allocation size.
* @param bytesToAlloc the initial number of bytes to be allocate.
*/
constructor(bytesToAlloc: number);

/**
* resizes the allocated memory to the specified number of bytes.
* @param bytesToAlloc the new size in bytes.
*/
refeed(bytesToAlloc: number): void;

/**
* returns the total number of bytes currently allocated.
* @returns {number} the size in bytes of allocated memory.
*/
memsize(): number;

/**
* allocates the number of bytes specified by the constructor each time it is called.
*/
feed(): void;

/**
* free all the allocated memory.
*/
flush(): void;

/**
* attempts to fill up all the available RAM.
*/
hog(): void;

```