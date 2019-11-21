#!/bin/bash

sudo adduser Jeff --force-badname

sudo groupadd TestMe

sudo usermod -a -G TestMe Jeff

sudo deluser Jeff

sudo deluser --remove-home Jeff
