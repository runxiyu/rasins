/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2022, 2023 Ferass El Hafidi <vitali64pmemail@protonmail.com>
 */
#ifndef PARSER_H
#define PARSER_H

int parseCommand(int, char **);
int splitCommand(char [4096], char *[4096]);

#endif /* PARSER_H */
