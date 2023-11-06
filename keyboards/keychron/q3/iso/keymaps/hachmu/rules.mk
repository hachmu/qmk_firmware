VIA_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes

SRC += keymap_user_config.c
SRC += rgb_matrix_user.c

VPATH += keyboards/keychron/common
SRC += keychron_common.c
SRC += keychron_factory_test_common.c
