package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	//"os"
)

func main(){
	response, err := http.Get("http://net.cs.uni-bonn.de/wg/cs/teaching/wt-201415/sysprog/")
	if err != nil {
		fmt.Printf("This Program has encountered an error while doing the GET-Request")	
	}
	body, err := ioutil.ReadAll(response.Body)
	if err != nil{
		fmt.Printf("This Program has encountered an error while reading the answer")
	}
	fmt.Printf("%s",response.Header)
	ioutil.WriteFile("website.html",body, 0664)
	
}
