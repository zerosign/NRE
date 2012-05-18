/*
 * TODO comment me
 *
 * Copyright (C) 2012, Nils Asmussen <nils@os.inf.tu-dresden.de>
 * Economic rights: Technische Universitaet Dresden (Germany)
 *
 * This file is part of NUL.
 *
 * NUL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * NUL is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 2 for more details.
 */

#include <arch/ExecEnv.h>
#include <kobj/Pd.h>
#include <kobj/Ec.h>
#include <cap/CapHolder.h>

namespace nul {

Pd *Pd::current() {
	return ExecEnv::get_current_pd();
}

Pd::Pd(Crd crd,Pd *pd) : ObjCap() {
	CapHolder ch;
	Syscalls::create_pd(ch.get(),crd,pd->sel());
	sel(ch.release());
}

}
