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

#include <service/ServiceInstance.h>
#include <service/Service.h>
#include <utcb/UtcbFrame.h>
#include <ScopedLock.h>
#include <ScopedPtr.h>

namespace nul {

void ServiceInstance::portal_newclient(cap_t,void *tls) {
	// TODO not everyone wants client-specific portals
	Service *s = reinterpret_cast<Service*>(tls);
	Pt *pt = s->new_client();
	UtcbFrameRef uf;
	uf.delegate(pt->cap());
}

ServiceInstance::ServiceInstance(Service* s,cpu_t cpu) : _s(s), _ec(), _pt(), _sm() {
	// multiple things might throw here
	ScopedPtr<LocalEc> ec(new LocalEc(s,cpu));
	ScopedPtr<Pt> pt(new Pt(ec.get(),portal_newclient));

	// register
	UtcbFrame uf;
	uf.delegate(pt->cap());
	uf << String(s->name()) << cpu;
	CPU::current().reg_pt->call(uf);

	_ec = ec.release();
	_pt = pt.release();
}

}