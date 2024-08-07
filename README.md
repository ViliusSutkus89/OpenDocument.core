# OpenDocument.core

![build status](https://github.com/opendocument-app/OpenDocument.core/workflows/build_test/badge.svg)

C++ library to visualize files, especially documents, in HTML.

## Supported files

- [odt](https://github.com/opendocument-app/OpenDocument.core/issues/92), [odp](https://github.com/opendocument-app/OpenDocument.core/issues/93), [ods](https://github.com/opendocument-app/OpenDocument.core/issues/94), [odg](https://github.com/opendocument-app/OpenDocument.core/issues/96) ([OpenOffice / LibreOffice](https://github.com/opendocument-app/OpenDocument.core/issues/111))
- [docx](https://github.com/opendocument-app/OpenDocument.core/issues/86), [pptx](https://github.com/opendocument-app/OpenDocument.core/issues/85), [xlsx](https://github.com/opendocument-app/OpenDocument.core/issues/87) ([Microsoft Office Open XML](https://github.com/opendocument-app/OpenDocument.core/issues/112))
- [zip](https://github.com/opendocument-app/OpenDocument.core/issues/109)
- [cfb](https://github.com/opendocument-app/OpenDocument.core/issues/110) (Microsoft Compound File Binary File Format)

## Unsupported files

- [csv](https://github.com/opendocument-app/OpenDocument.core/issues/107)
- [pdf](https://github.com/opendocument-app/OpenDocument.core/issues/108)
- [doc](https://github.com/opendocument-app/OpenDocument.core/issues/104), [ppt](https://github.com/opendocument-app/OpenDocument.core/issues/106), [xls](https://github.com/opendocument-app/OpenDocument.core/issues/105)

## References

Currently, used as backend for [OpenDocument.droid](https://github.com/opendocument-app/OpenDocument.droid) and [OpenDocument.ios](https://github.com/opendocument-app/OpenDocument.ios).

Replaces legacy projects [OpenDocument.java](https://github.com/andiwand/OpenDocument.java), [JOpenDocument](https://github.com/andiwand/JOpenDocument) and [svm](https://github.com/andiwand/svm).

Potential test files: https://file-examples.com/

## [Documentation](docs/README.md)

## Build

This project comes with CMake as a build system and Conan as package manager. In principle they should be independent and one can build without Conan.

Using Conan one can use our Artifactory as a Conan remote for convenience: https://artifactory.opendocument.app/

As an alternative to the Conan remote you can also export the package locally via Conan i.e. `conan export . --name odrcore --version VERSION` (fill `VERSION` with something appropriate).

## Version

Versions and history are tracked on [GitHub](https://github.com/opendocument-app/OpenDocument.core).
