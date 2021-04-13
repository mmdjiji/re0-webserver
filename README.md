# Re0 Web Server

![avatar](https://cdn.jsdelivr.net/gh/mmdjiji/re0-webserver@main/assets/re0.jpg)

This is my first `Re0` series project. `Re0` means do something start from the very beginning, from [Re:ゼロから始める異世界生活](https://ja.wikipedia.org/wiki/Re:%E3%82%BC%E3%83%AD%E3%81%8B%E3%82%89%E5%A7%8B%E3%82%81%E3%82%8B%E7%95%B0%E4%B8%96%E7%95%8C%E7%94%9F%E6%B4%BB).

Of course, [Rem(レム)](https://ja.wikipedia.org/wiki/Re:%E3%82%BC%E3%83%AD%E3%81%8B%E3%82%89%E5%A7%8B%E3%82%81%E3%82%8B%E7%95%B0%E4%B8%96%E7%95%8C%E7%94%9F%E6%B4%BB#%E3%82%A8%E3%83%9F%E3%83%AA%E3%82%A2%E9%99%A3%E5%96%B6) is my wife.

## Introduction
The project is a simple implementation of web server under HTTP/1.1 ([RFC 2616](https://tools.ietf.org/html/rfc2616)).

## Usage
```sh
make
./re0-webserver
```

## Configuration
Use `vim config.json` to change the fields follows:
```json
{
	"local_ip":	"0.0.0.0",
	"local_port":	80,
	"root":	"htdocs",
	"index":	"index.html",
	"access_log":	"access.log"
}
```

## Plan
- [x] Make a web server work.
- [x] Support `200 OK`, `404 Not Found`.
- [ ] Add Other fields.
- [ ] Finish 403 and other error codes.
- [ ] Make Linux compatible.
- [ ] Fix bug of path bypass.
- [ ] ...

## References
1. [RFC 2616](https://tools.ietf.org/html/rfc2616)
2. [HTTP Study By SpiritLing](https://www.kancloud.cn/spirit-ling/http-study)

## License
Author: [mmdjiji(JiJi)](https://mmdjiji.com). Open source by [GNU GPLv3.0](https://choosealicense.com/licenses/gpl-3.0/) license.
