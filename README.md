# FAQ
## I'm on Windows and WSL2 (Vmmem in particular) fills up my memory
Solution: limit WSL2 RAM usage via `.wslconfig`. See here for complete instructions: https://github.com/microsoft/WSL/issues/4166#issuecomment-526725261

## docker.errors.DockerException: Error while fetching server API version
Solution: Docker is probably not running, check if it's running.