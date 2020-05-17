#!/bin/bash

docker stop $(docker ps -a -q)
docker rm $(docker ps -a -q)

docker rm -vf $(docker ps -a -q)            # Delete all containers include volume use
docker rmi -f $(docker images -a -q)        # Delete all images

docker system prune -f
docker system prune -a --volumes -f   # Delete everything
