#pragma once

#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <stdbool.h>

//Optional basic type
#define opt_bt(_bt) struct { bool present; _bt value; }

//Optional var
#define opt_v(_t) struct { bool present; TYEPOF(_t) value; }

//Optional struct of type _t
#define opt_t(_t) struct { bool present; TYPEOF(_t) value; } (opt_##_t)

#define has_value(opt) opt.present
#define value(opt) opt.value
#define set_opt(opt, val) opt.value = val; opt.present = true
#define set_opt_t(opt, val) opt.value = val; opt.present = true
#define set_opt_t_mem(opt, val, mem) opt.value.##mem = val; opt.present = true

#endif

