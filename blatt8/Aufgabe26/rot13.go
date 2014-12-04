package main

import (
	"bufio"
	"os"
	"fmt"
	"unsafe"
	//#include <stdlib.h>
	//#include "rot13.h"
	"C"
)

const delim = '\n'

func main() {

	r := bufio.NewReader(os.Stdin)
	
	for true{
		fmt.Println("Please enter the string that you want to encrypt:")
		line, err := r.ReadString(delim)
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}
		fmt.Println("You entered the following text:")
		fmt.Print(line)

		fmt.Println("The encrypted text is:")
		fmt.Println(encrypt(line))
		
	}

}

func encrypt(unencrypted string) string{
	cunencrypted := C.CString(unencrypted)
	/*'defer' calls the function when the outer function returns
	 * This prevents that cunencrypted is not freed, for example if the function encrypt return unexpectedly
	 */
	defer C.free(unsafe.Pointer(cunencrypted))

	C.rot13_str(cunencrypted)

	return C.GoString(cunencrypted)
}
