#!/usr/bin/env just --justfile

alias s := setup
alias c := compile
alias r := run
alias d := docs

browser := "firefox"

default: setup compile run

setup:
    meson setup builddir

compile:
    meson compile -C builddir

run:
    builddir/clox

docs_generate:
    doxygen

docs_open:
    {{ browser }} docs/html/index.html

docs: docs_generate docs_open
