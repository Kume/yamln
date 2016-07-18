TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    yamln \
    tests \
    activeYaml

yamln.deponds = activeYaml
