#!/usr/bin/env just --justfile

alias s := setup
alias c := compile
alias r := run

default: setup compile run

setup:
    meson setup builddir

compile:
    meson compile -C builddir

run:
    builddir/clox
