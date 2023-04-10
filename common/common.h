/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#ifndef COMMON_H
#define COMMON_H

#ifdef REQ_PRINT_USAGE
int print_usage(char *name, char *desc, char *params, char *version);
#endif
#ifdef REQ_ERRPRINT
int errprint(char *argv0, char *prefix, int err);
#endif

#endif /* COMMON_H */
