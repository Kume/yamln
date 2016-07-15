TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    libyaml \
    yamln \

yamln.deponds = libyaml
