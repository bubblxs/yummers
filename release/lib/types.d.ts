declare module "#yummers" {
        /**
         * memory allocation manager that handles your nodejs application lack of comsuming RAM.
        */
        export class Yummers {
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
                 * attempts to fill up the available RAM.
                */
                hog(): void;
        }
}