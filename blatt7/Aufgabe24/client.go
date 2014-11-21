package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
	"strings"
)

func main() {
	fmt.Println("Starting up!")
	//build a request object
	res, err := http.Get("http://net.cs.uni-bonn.de/de/wg/cs/lehre/ws-201415/sysprog/")
	if err != nil {
		fmt.Println("Cannot connect to sysprog hompage!")
		return
	}
	defer res.Body.Close()
	body, err := ioutil.ReadAll(res.Body)
	if err != nil {
		fmt.Println("Cannot download sysprog homepage!")
		return
	}

	var bodyStr string = string(body[:])
	blattStart := "fileadmin/ag/martini/lehre/1415ws/SysProg/UeZettel/"
	blattEnd := ".pdf"
	fmt.Println("Verfügbare Blätter:")

	for i := 0; i < 20; i++ {
		blattName := fmt.Sprintf("Uebungsblatt%02d", i)
		curBlatt := blattStart + blattName + blattEnd
		if strings.Contains(bodyStr, curBlatt) {
			fmt.Println(blattName)
		}
	}

	ioutil.WriteFile("sysprog.html", body, 0664)
}
