package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

type File struct {
	//l    log.Logger
	path string
}

func NewFile(fp string) *File {
	return &File{fp}
}

func (f *File) ReadFile() ([]string, error) {
	var fileContent []string
	file, err := os.Open(f.path)
	if err != nil {
		log.Panic(err)
	}

	defer file.Close()
	//search for matching id in file with given from request
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		text := fmt.Sprint(scanner.Text(), "\n")
		fileContent = append(fileContent, text)
	}
	return fileContent, err
}

func (f *File) WriteToFile(code string) bool {
	file, err := os.OpenFile(f.path, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		panic(err)
	}
	//CONCAT 2 STRINGS
	str := fmt.Sprint(code, "\n")
	if _, err := file.WriteString(str); err != nil {
		panic(err)
	}
	defer file.Close()

	return err == nil
}
