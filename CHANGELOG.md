Changelog
=========

dev
---

* (nothing yet)

0.2 (2016-03-14)
----------------

* Added basic support for the [file-analyzing
  service](https://retdec.com/api/docs/fileinfo.html). Also added a sample tool
  that uses this service to analyze binary files (`fileinfo`).
* Added basic support for the [test
  service](https://retdec.com/api/docs/test.html). It can be used to verify
  API-key authentications.
* Added a new subclass of `ApiError`: `AuthError`. It is thrown when there is
  an authentication or authorization error.

0.1 (2015-12-06)
----------------

Initial release.
