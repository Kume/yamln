TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    yamln \
    activeYaml

yamln.deponds = activeYaml
tests.depends = activeYaml
