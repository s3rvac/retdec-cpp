Changelog
=========

dev
---

* Added basic support for the [file-analyzing
  service](https://retdec.com/api/docs/fileinfo.html). Also added a sample tool
  that uses this service to analyze binary files (`fileinfo`).
* Added a new subclass of `ApiError`: `AuthError`. It is thrown when there is
  an authentication or authorization error.

0.1 (2015-12-06)
----------------

Initial release.
