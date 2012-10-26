/* FluidSphOpenCL.cpp
	Copyright (C) 2012 Jackson Lee

	ZLib license
	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.
	
	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:
	
	1. The origin of this software must not be misrepresented; you must not
	   claim that you wrote the original software. If you use this software
	   in a product, an acknowledgment in the product documentation would be
	   appreciated but is not required.
	2. Altered source versions must be plainly marked as such, and must not be
	   misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.
*/
#include "FluidSphOpenCL.h"

#include "../FluidParameters.h"
#include "../FluidParticles.h"

void FluidSphOpenCL::writeToOpenCL(cl_command_queue queue, const FluidParametersLocal &FL, FluidParticles *particles)
{
	m_localParameters.resize(1);
	m_localParameters.copyFromHostPointer(&FL, 1, 0, false);
	
	int numParticles = particles->size();
	m_pos.resize(numParticles);
	m_vel_eval.resize(numParticles);
	m_sph_force.resize(numParticles);
	m_pressure.resize(numParticles);
	m_invDensity.resize(numParticles);
	m_neighborTable.resize(numParticles);
	
	m_pos.copyFromHost(particles->m_pos, false);
	m_vel_eval.copyFromHost(particles->m_vel_eval, false);
	
	clFinish(queue);
}
void FluidSphOpenCL::readFromOpenCL(cl_command_queue queue, FluidParticles *particles)
{
	m_sph_force.copyToHost(particles->m_sph_force, false);
	clFinish(queue);
}
	