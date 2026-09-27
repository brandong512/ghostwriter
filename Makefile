CRAFT_ROOT     := C:/CraftRoot
CRAFT_ENV      := $(CRAFT_ROOT)/craft/craftenv.ps1
APP_EXECUTABLE := $(CRAFT_ROOT)/bin/ghostwriter.exe
PACKAGE_OUTPUT := $(CRAFT_ROOT)/tmp
BLUEPRINT      := kde/applications/ghostwriter
SOURCE_OPTION  := $(BLUEPRINT).srcDir=$(CURDIR)

BUILD_STAMP    := build/craft-build.stamp
STAMP_PATH     := $(CURDIR)/$(BUILD_STAMP)

SHELL          := powershell.exe
.SHELLFLAGS    := -NoProfile -ExecutionPolicy Bypass -Command

LOAD_CRAFT     := . '$(CRAFT_ENV)' 2>$$null | Out-Null;
CRAFT          := craft --options '$(SOURCE_OPTION)'
STOP_ON_ERROR  := if ($$LASTEXITCODE) { exit $$LASTEXITCODE };

find_files      = $(foreach entry,$(wildcard $(1:=/*)),$(call find_files,$(entry),$(2)) $(filter $(subst *,%,$(2)),$(entry)))

WATCHED_SOURCES := CMakeLists.txt resources.qrc icons.qrc \
                   $(call find_files,src,*.cpp *.h *.ui *.txt) \
                   $(call find_files,resources,*.css *.html *.qss *.png *.svg *.ttf) \
                   $(call find_files,3rdparty/qwindowkit/src,*.cpp *.h *.txt *.cmake)

.DEFAULT_GOAL := run
.PHONY: run build zip installer rebuild

run: build
	$(LOAD_CRAFT) & '$(APP_EXECUTABLE)'

build: $(BUILD_STAMP)

$(BUILD_STAMP): $(WATCHED_SOURCES)
	$(LOAD_CRAFT) if (Test-Path '$(STAMP_PATH)') { $(CRAFT) --compile --install --qmerge $(BLUEPRINT) } else { $(CRAFT) -i $(BLUEPRINT) }; $(STOP_ON_ERROR) New-Item -ItemType File -Force '$(STAMP_PATH)' | Out-Null

rebuild:
	Remove-Item -Force -ErrorAction SilentlyContinue '$(STAMP_PATH)'
	$(MAKE) build

zip: build
	$(LOAD_CRAFT) $(CRAFT) --options '[Packager]PackageType=PortablePackager' --options '[Packager]7ZipArchiveType=zip' --package $(BLUEPRINT); $(STOP_ON_ERROR) Write-Host 'Zip written to $(PACKAGE_OUTPUT)'

installer: build
	$(LOAD_CRAFT) craft nsis; $(STOP_ON_ERROR) $(CRAFT) --package $(BLUEPRINT); $(STOP_ON_ERROR) Write-Host 'Installer written to $(PACKAGE_OUTPUT)'
