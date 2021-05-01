# Requirements
- Docker
- Docker Compose

# Usage
- Open a command-line terminal in the top-level folder of this project
- Run `docker compose up` (if it doesn't work, try `docker-compose up`; you might be using an older version of the Docker CLI)
- After setup, Grafana will be running on port 3000 and PostgreSQL will be running on port 5432
    - Grafana can be accessed at [localhost:3000](http://localhost:3000/d/2UjSB19Gz/main-dashboard?orgId=1&from=now-15m&to=now&refresh=5s)
    - PostgreSQL can be accessed at [localhost:5432](localhost:5432)

# FAQ
## I'm on Windows and WSL2 (Vmmem in particular) fills up my memory
Solution: limit WSL2 RAM usage via `.wslconfig`. See here for complete instructions: https://github.com/microsoft/WSL/issues/4166#issuecomment-526725261

## docker.errors.DockerException: Error while fetching server API version
Solution: Docker is probably not running, check if it's running.

## PostgreSQL initialization is failing
There might be some leftover files from previous Docker initializations. Try running this:

1. `docker-compose rm`
2. `docker-compose build`
3. `docker-compose up`

Check if initialization is now completed properly.