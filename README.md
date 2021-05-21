# Formula Student telemetry base station system
This repository contains code for the base station system of a Formula Student racing team.

The system is divided in two main components: the **database**, based on PostgreSQL+TimescaleDB, and the **dashboard**, based on Grafana.

Docker is used to containerize the system.

## Requirements
- Docker
- Docker Compose (optional, for older Docker versions that do no include the `compose` CLI command)

## Usage
- Open a command-line terminal in the top-level folder of this project
- Run `docker compose up` (if it doesn't work, try `docker-compose up`; you might be using an older version of the Docker CLI)
- After setup, Grafana will be running on port 3000 and PostgreSQL will be running on port 5432
    - Grafana can be accessed at [localhost:3000](http://localhost:3000/d/2UjSB19Gz/main-dashboard?orgId=1&from=now-15m&to=now&refresh=5s)
    - PostgreSQL can be accessed at [localhost:5432](localhost:5432)
        - Data is stored on the host machine at `/data/db/`, and will persist even when containers are stopped or removed 

## FAQ
### I'm on Windows and WSL2 (Vmmem in particular) fills up my memory
Solution: limit WSL2 RAM usage via `.wslconfig`. See here for complete instructions: https://github.com/microsoft/WSL/issues/4166#issuecomment-526725261

### docker.errors.DockerException: Error while fetching server API version
Solution: Docker is probably not running, check if it's running.

### PostgreSQL initialization is failing
There might be some leftover files from previous Docker initializations. Try running this:

1. `docker-compose rm`
2. `docker-compose build`
3. `docker-compose up`

Check if initialization is now completed properly. If it fails, attempt to remove volumes with `docker-compose down` and try again.

## Useful links
This repository contains the code for the remaining components of the telemetry system: https://github.com/rdimaio/can-box