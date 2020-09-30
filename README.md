<div align="center">
  <img src="https://raw.githubusercontent.com/SwitchbladeBot/bastille/master/assets/Banner.png"/>
  <br>
  <img src="https://www.codefactor.io/repository/github/switchbladebot/bastille/badge">
  <img src="https://img.shields.io/github/workflow/status/SwitchbladeBot/bastille/cpp">
  <img src="https://img.shields.io/github/license/SwitchbladeBot/bastille">
</div>

## Bastille
Bastille is a free and open source Javascript container runtime based on the Google V8 engine and inspired by Cloudflare workers. It is designed to handle unsafe code and allow multiple executions at once. This is designed to open API access to some discord endpoints to allow custom scripting, it does not handle event dispatching, it is just the worker.

## Build
Has been tested on Ubuntu linux
```bash
git clone https://github.com/switchbladebot/bastille.git
cd bastille
bash setup.sh
cmake CMakeLists.txt
cmake --build cmake-build-debug --target Bastille -- -j4
```

## Roadmap
- [x] Javascript VM
- [ ] Native module support
- [ ] REST Server
	- [ ] Authorization
	- [x] Endpoints
- [ ] Standard Library
	- [x] Console
	- [ ] Fetch
	- [ ] Discord
