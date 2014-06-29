#!/bin/sh
function envmod() {
	./envmod.exe $@ save "$$.sh"
	. "$$.sh"
	rm "$$.sh"
}
