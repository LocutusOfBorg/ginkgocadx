/*
 * This file is part of Ginkgo CADx
 *
 * Copyright (c) 2015-2016 Gert Wollny
 * Copyright (c) 2008-2014 MetaEmotion S.L. All rights reserved.
 *
 * Ginkgo CADx is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser Public License
 * along with Ginkgo CADx; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once
#include <api/api.h>
#include <api/controllers/icontroladoracciones.h>
#include <api/controllers/icontroladorvistas.h>
#include <list>
#include <map>

class wxCriticalSection;
namespace GNC
{
namespace GCS
{
class EXTAPI ControladorAcciones: public IControladorAcciones, public IObservadorVistas
{
public:
        static ControladorAcciones* Instance();
        static void FreeInstance();

        virtual void PushAccion(GNC::GCS::IVista* pVista, GNC::GCS::Ptr<Accion> pAccion);
        virtual void Deshacer(GNC::GCS::IVista* pVista);
        virtual void Hacer(GNC::GCS::IVista* pVista);
        virtual bool PuedeHacer(GNC::GCS::IVista* pVista, std::string& nombreAccion);
        virtual bool PuedeDeshacer(GNC::GCS::IVista* pVista, std::string& nombreAccion);

protected:
        static ControladorAcciones* m_pInstance;
        ControladorAcciones();
        ~ControladorAcciones();

        void OnVistaDestruida(GNC::GCS::IVista* pVista);

        typedef std::list<GNC::GCS::Ptr<Accion> > TListaAcciones;
        typedef struct TPilaDeshacer {
                TListaAcciones m_listaAcciones;
                TListaAcciones::iterator m_iteradorAcciones;
                TPilaDeshacer()
                {
                        m_iteradorAcciones = m_listaAcciones.end();
                }
                ~TPilaDeshacer()
                {
                        m_listaAcciones.clear();
                }
        } TPilaDeshacer;
        typedef std::map<IVista*, TPilaDeshacer*> TMapaVista;
        TMapaVista m_mapaAcciones;

        wxCriticalSection* m_pCriticalSection;


};
}
}
