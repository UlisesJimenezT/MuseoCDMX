#ifndef CATALOGO_MUSEO_H
#define CATALOGO_MUSEO_H

#include <sceneobject.h>

// Museo
const char* const MUSEUM_ARCHITECTURE_FILE = "hacienda.fbx";

// Techos
const char* const MUSEUM_ROOF_FILE = "hacienda_techos.fbx";

// FBX 
const char* const MUSEUM_MODELS_DIR = "models/museo/";

// Inicio 
const glm::vec3 MUSEUM_SPAWN_POSITION(0.0f, 0.0f, 9.0f);

// Piezas, nombre, fbx, sala, posicion, rotacion, escala, material
const CatalogEntry kCatalogoMuseo[] = {

	// sala juguetes
	{ "Balero", "balero.fbx", ROOM_JUGUETES, {-16.1f, 0.9f, 15.05f}, {0.0f, 180.0f, 0.0f}, {0.75f, 0.75f, 0.75f}, MAT_MATE },
	{ "Barquito de juguete", "barquito_de_juguete.fbx", ROOM_JUGUETES, {-9.8f, 0.8f, 17.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Caballito de madera", "caballito_de_madera.fbx", ROOM_JUGUETES, {-20.3f, 0.25f, 15.05f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Camioneta de madera", "camioneta_de_madera.fbx", ROOM_JUGUETES, {-14.0f, 0.8f, 17.5f}, {0.0f, -30.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Canicas", "canicas.fbx", ROOM_JUGUETES, {-16.1f, 0.8f, 17.5f}, {0.0f, 0.0f, 0.0f}, {0.75f, 0.75f, 0.75f}, MAT_TRANSLUCIDO },
	{ "Carrito de madera", "carrito_de_madera.fbx", ROOM_JUGUETES, {-11.9f, 0.8f, 17.5f}, {0.0f, 30.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Loteria mexicana", "loteria_mexicana.fbx", ROOM_JUGUETES, {-20.3f, 0.25f, 19.95f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Pinata", "pinata.fbx", ROOM_JUGUETES, {-15.05f, 4.5f, 16.275f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Pirinola", "pirinola.fbx", ROOM_JUGUETES, {-11.9f, 0.9f, 15.05f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Resortera", "resortera.fbx", ROOM_JUGUETES, {-11.9f, 0.9f, 19.95f}, {0.0f, 180.0f, 0.0f}, {0.75f, 0.75f, 0.75f}, MAT_MATE },
	{ "Tablitas de madera", "tablitas_de_madera.fbx", ROOM_JUGUETES, {-18.2f, 0.9f, 19.95f}, {0.0f, 180.0f, 0.0f}, {0.75f, 0.75f, 0.75f}, MAT_MATE },
	{ "Tren de juguete", "tren_de_juguete.fbx", ROOM_JUGUETES, {-15.05f, 0.8f, 19.95f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Trompo", "trompo.fbx", ROOM_JUGUETES, {-14.0f, 0.9f, 15.05f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Yoyo", "yoyo.fbx", ROOM_JUGUETES, {-9.8f, 0.975f, 19.95f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Avion de juguete", "avion_de_juguete.fbx", ROOM_JUGUETES, {-10.85f, 4.4f, 18.725f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Alebrije", "alebrije.fbx", ROOM_JUGUETES, {-18.2f, 0.45f, 15.05f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Marioneta", "marioneta.fbx", ROOM_JUGUETES, {-20.3f, 2.3f, 17.5f}, {0.0f, 0.0f, 0.0f}, {0.75f, 0.75f, 0.75f}, MAT_MATE },
	{ "Matracas", "matracas.fbx", ROOM_JUGUETES, {-7.7f, 0.9f, 17.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Sonaja de calavera", "sonaja_de_calavera.fbx", ROOM_JUGUETES, {-7.7f, 0.9f, 15.05f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },

    // sala xochi
	{ "Trajinera", "trajinera.fbx", ROOM_XOCHIMILCO, {-16.1f, 0.18f, -20.93f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Ajolote", "ajolote.fbx", ROOM_XOCHIMILCO, {-18.9f, 0.9f, -16.8f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_TRANSLUCIDO },
	{ "Maqueta de chinampa", "maqueta_de_chinampa.fbx", ROOM_XOCHIMILCO, {-21.35f, 0.8f, -16.8f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Garza", "garza.fbx", ROOM_XOCHIMILCO, {-16.45f, 0.25f, -16.8f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Canoa", "canoa.fbx", ROOM_XOCHIMILCO, {-11.2f, 0.28f, -20.93f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Embarcadero", "embarcadero.fbx", ROOM_XOCHIMILCO, {-14.0f, 0.0f, -18.97f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Remo", "remo.fbx", ROOM_XOCHIMILCO, {-7.0f, 0.0f, -21.7f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Ahuejote", "ahuejote.fbx", ROOM_XOCHIMILCO, {-21.35f, 0.0f, -14.56f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Canasta de flores", "canasta_de_flores.fbx", ROOM_XOCHIMILCO, {-14.0f, 0.9f, -16.8f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Puesto de flores", "puesto_de_flores.fbx", ROOM_XOCHIMILCO, {-18.9f, 0.0f, -14.56f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Huacal de cultivo", "huacal_de_cultivo.fbx", ROOM_XOCHIMILCO, {-13.65f, 0.25f, -14.56f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Nenufares", "nenufares.fbx", ROOM_XOCHIMILCO, {-16.1f, 0.01f, -14.56f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_TRANSLUCIDO },
	{ "Maqueta de canal", "maqueta_de_canal.fbx", ROOM_XOCHIMILCO, {-11.55f, 0.8f, -16.8f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Herramienta agricola tradicional", "herramienta_agricola_tradicional.fbx", ROOM_XOCHIMILCO, {-11.55f, 0.0f, -14.56f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_METALICO },
	{ "Panel de biodiversidad de Xochimilco", "panel_de_biodiversidad_de_xochimilco.fbx", ROOM_XOCHIMILCO, {-6.3f, 0.0f, -14.56f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Rana de Xochimilco", "rana_de_xochimilco.fbx", ROOM_XOCHIMILCO, {-6.3f, 0.9f, -16.8f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Carpa (pez del canal)", "carpa_pez_del_canal.fbx", ROOM_XOCHIMILCO, {-16.1f, 0.21f, -14.56f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Maceta con cempasuchil", "maceta_con_cempasuchil.fbx", ROOM_XOCHIMILCO, {-5.32f, 0.0f, -21.91f}, {0.0f, 90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },

	// sala dia de muertos
	{ "Ofrenda monumental", "ofrenda_estructura_del_altar.fbx", ROOM_DIA_DE_MUERTOS, {18.025f, 0.0f, -6.79f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Arco de cempasuchil", "arco_de_cempasuchil.fbx", ROOM_DIA_DE_MUERTOS, {18.025f, 0.0f, -6.79f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Catrina", "catrina.fbx", ROOM_DIA_DE_MUERTOS, {15.12f, 0.25f, -1.4f}, {0.0f, 20.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Catrin de levita", "catrin.fbx", ROOM_DIA_DE_MUERTOS, {20.93f, 0.25f, -1.4f}, {0.0f, -20.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Xoloitzcuintle", "xoloitzcuintle.fbx", ROOM_DIA_DE_MUERTOS, {16.8f, 0.0f, 1.05f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Calavera de azucar", "calavera_de_azucar.fbx", ROOM_DIA_DE_MUERTOS, {14.7f, 0.9f, 1.75f}, {0.0f, 90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Pan de muerto", "pan_de_muerto.fbx", ROOM_DIA_DE_MUERTOS, {14.7f, 0.9f, 4.2f}, {0.0f, 90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Copalero", "copalero.fbx", ROOM_DIA_DE_MUERTOS, {21.35f, 0.9f, 1.75f}, {0.0f, -90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Candelabro", "candelabro.fbx", ROOM_DIA_DE_MUERTOS, {15.4f, 0.0f, -4.9f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_METALICO },
	{ "Florero con cempasuchil", "florero_con_cempasuchil.fbx", ROOM_DIA_DE_MUERTOS, {14.7f, 0.9f, 6.65f}, {0.0f, 90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Retrato enmarcado", "retrato_enmarcado.fbx", ROOM_DIA_DE_MUERTOS, {21.35f, 0.9f, 11.55f}, {0.0f, -90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_METALICO },
	{ "Papel picado", "papel_picado.fbx", ROOM_DIA_DE_MUERTOS, {18.025f, 4.7f, -2.1f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_TRANSLUCIDO },
	{ "Canasta de frutas", "canasta_de_frutas.fbx", ROOM_DIA_DE_MUERTOS, {21.35f, 0.8f, 6.65f}, {0.0f, -90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Alebrije del altar", "alebrije_altar.fbx", ROOM_DIA_DE_MUERTOS, {21.35f, 0.45f, 9.1f}, {0.0f, -90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Farol", "farol.fbx", ROOM_DIA_DE_MUERTOS, {14.7f, 0.9f, 9.1f}, {0.0f, 90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_METALICO },
	{ "Jarrito de barro", "jarrito_de_barro.fbx", ROOM_DIA_DE_MUERTOS, {21.35f, 0.9f, 4.2f}, {0.0f, -90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Tapete de aserrin", "tapete_de_aserrin.fbx", ROOM_DIA_DE_MUERTOS, {18.025f, 0.0f, -3.57f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Cruz de sal", "cruz_de_sal.fbx", ROOM_DIA_DE_MUERTOS, {18.025f, 0.0f, -1.05f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Cirio pascual", "cirio_pascual.fbx", ROOM_DIA_DE_MUERTOS, {20.65f, 0.0f, -4.9f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Corona de flores", "corona_de_flores.fbx", ROOM_DIA_DE_MUERTOS, {14.7f, 0.0f, 11.55f}, {0.0f, 90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },

	// sala gastro
	{ "Cazuela de mole", "cazuela_de_mole.fbx", ROOM_GASTRONOMIA, {-20.3f, 0.8f, -9.1f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Olla de barro con frijoles", "olla_de_barro_con_frijoles.fbx", ROOM_GASTRONOMIA, {-20.3f, 0.8f, -6.65f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Comal con tortillas", "comal_con_tortillas.fbx", ROOM_GASTRONOMIA, {-20.3f, 0.8f, -4.2f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Taza de chocolate", "taza_de_chocolate.fbx", ROOM_GASTRONOMIA, {-16.45f, 0.8f, -9.1f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_PLASTICO },
	{ "Molinillo", "molinillo.fbx", ROOM_GASTRONOMIA, {-16.45f, 0.8f, -6.65f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Calabaza en tacha", "calabaza_en_tacha.fbx", ROOM_GASTRONOMIA, {-20.3f, 0.8f, 0.7f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Piloncillo", "piloncillo.fbx", ROOM_GASTRONOMIA, {-16.45f, 0.8f, 0.7f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Botella de mezcal", "botella_de_mezcal.fbx", ROOM_GASTRONOMIA, {-16.45f, 0.8f, 3.15f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_TRANSLUCIDO },
	{ "Jarra de pulque", "jarra_de_pulque.fbx", ROOM_GASTRONOMIA, {-20.3f, 0.8f, 5.6f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Tamales en hoja", "tamales_en_hoja.fbx", ROOM_GASTRONOMIA, {-20.3f, 0.8f, -1.75f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Atole en cantarito", "atole_en_cantarito.fbx", ROOM_GASTRONOMIA, {-16.45f, 0.8f, -4.2f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Dulce de tejocote", "dulce_de_tejocote.fbx", ROOM_GASTRONOMIA, {-16.45f, 0.8f, -1.75f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Calaverita de chocolate", "calaverita_de_chocolate.fbx", ROOM_GASTRONOMIA, {-21.91f, 0.9f, 10.85f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Plato con sal", "plato_con_sal.fbx", ROOM_GASTRONOMIA, {-20.23f, 0.9f, 10.85f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Vaso de agua bendita", "vaso_de_agua_bendita.fbx", ROOM_GASTRONOMIA, {-18.55f, 0.9f, 10.85f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_TRANSLUCIDO },
	{ "Canasta de panaderia", "canasta_de_panaderia.fbx", ROOM_GASTRONOMIA, {-20.3f, 0.8f, 3.15f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Botella de tequila", "botella_de_tequila.fbx", ROOM_GASTRONOMIA, {-16.45f, 0.8f, 5.6f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_TRANSLUCIDO },
	{ "Jicara artesanal", "jicara_artesanal.fbx", ROOM_GASTRONOMIA, {-20.3f, 0.8f, 8.05f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_PLASTICO },
	{ "Metate de piedra", "metate_de_piedra.fbx", ROOM_GASTRONOMIA, {-14.98f, 0.45f, 10.85f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Molcajete", "molcajete.fbx", ROOM_GASTRONOMIA, {-16.87f, 0.9f, 10.85f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },

	// sala lucha
	{ "Ring de lucha libre", "ring_de_lucha_libre.fbx", ROOM_LUCHA_LIBRE, {11.9f, 0.0f, -18.2f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Mascara azul", "mascara_azul.fbx", ROOM_LUCHA_LIBRE, {5.6f, 0.9f, -21.35f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Mascara roja", "mascara_roja.fbx", ROOM_LUCHA_LIBRE, {8.05f, 0.9f, -21.35f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Mascara clasica mexicana", "mascara_clasica.fbx", ROOM_LUCHA_LIBRE, {8.05f, 0.9f, -18.9f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_METALICO },
	{ "Cinturon de campeon", "cinturon_de_campeon.fbx", ROOM_LUCHA_LIBRE, {5.6f, 0.45f, -15.75f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_METALICO },
	{ "Guantes de lucha", "guantes_de_lucha.fbx", ROOM_LUCHA_LIBRE, {8.05f, 0.9f, -15.75f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Botas de luchador", "botas_de_luchador.fbx", ROOM_LUCHA_LIBRE, {16.1f, 0.25f, -21.35f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Campana del ring", "campana_del_ring.fbx", ROOM_LUCHA_LIBRE, {16.1f, 0.8f, -18.9f}, {0.0f, -90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_METALICO },
	{ "Trofeo", "trofeo.fbx", ROOM_LUCHA_LIBRE, {18.9f, 0.9f, -21.35f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_METALICO },
	{ "Cartel de funcion", "cartel_de_funcion.fbx", ROOM_LUCHA_LIBRE, {11.9f, 0.0f, -21.05f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Silla de arena", "silla_de_arena.fbx", ROOM_LUCHA_LIBRE, {16.1f, 0.0f, -16.45f}, {0.0f, -90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_METALICO },
	{ "Reflector", "reflector.fbx", ROOM_LUCHA_LIBRE, {18.9f, 4.5f, -18.9f}, {0.0f, -90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_METALICO },
	{ "Luchador 1 (tecnico)", "luchador_1.fbx", ROOM_LUCHA_LIBRE, {11.2f, 1.005f, -18.2f}, {0.0f, 90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Luchador 2 (rudo)", "luchador_2.fbx", ROOM_LUCHA_LIBRE, {12.74f, 1.005f, -18.2f}, {0.0f, -90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Barrera de publico", "barrera_de_publico.fbx", ROOM_LUCHA_LIBRE, {11.9f, 0.0f, -14.7f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_METALICO },
	{ "Megafono", "megafono.fbx", ROOM_LUCHA_LIBRE, {18.9f, 0.8f, -16.45f}, {0.0f, -90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_PLASTICO },
	{ "Banco del esquinero", "banco_esquinero.fbx", ROOM_LUCHA_LIBRE, {14.91f, 0.0f, -15.12f}, {0.0f, -45.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Maletin de campeonato", "maletin_de_campeonato.fbx", ROOM_LUCHA_LIBRE, {18.9f, 0.9f, -14.35f}, {0.0f, 180.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_METALICO },
	{ "Galeria de lucha", "galeria_lucha.fbx", ROOM_LUCHA_LIBRE, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },

	// panteon
	{ "Tumba decorada", "tumba_decorada.fbx", ROOM_PANTEON, {32.55f, 0.0f, -7.0f}, {0.0f, 90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Lapida antigua", "lapida_antigua.fbx", ROOM_PANTEON, {41.65f, 0.0f, -7.0f}, {0.0f, -90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Cruz de madera", "cruz_de_madera.fbx", ROOM_PANTEON, {32.55f, 0.0f, 7.0f}, {0.0f, 90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Guitarra de Paracho", "guitarra_mexicana.fbx", ROOM_PANTEON, {33.775f, 0.57f, -21.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Trompeta de mariachi", "trompeta_mariachi.fbx", ROOM_PANTEON, {39.025f, 1.22f, -21.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_METALICO },
	{ "Violin huasteco", "violin_huasteco.fbx", ROOM_PANTEON, {35.525f, 0.77f, -21.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_PLASTICO },
	{ "Sombrero charro", "sombrero_charro.fbx", ROOM_PANTEON, {40.775f, 1.22f, -21.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Mascara de viejo", "mascara_de_viejo.fbx", ROOM_PANTEON, {33.775f, 1.22f, -18.2f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Arbol de la vida", "arbol_de_la_vida.fbx", ROOM_PANTEON, {37.275f, 0.77f, -21.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Candelero de talavera", "candelero_de_talavera.fbx", ROOM_PANTEON, {35.35f, 0.9f, -4.9f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_PLASTICO },
	{ "Florero de terciopelo", "florero_de_terciopelo.fbx", ROOM_PANTEON, {38.85f, 0.9f, -4.9f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Canasta de petalos", "canasta_de_petalos.fbx", ROOM_PANTEON, {35.35f, 0.0f, 4.9f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Sahumerio", "sahumerio_maya.fbx", ROOM_PANTEON, {38.85f, 0.9f, 4.9f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Tecolote alebrije", "tecolote_alebrije.fbx", ROOM_PANTEON, {40.775f, 1.22f, -18.2f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Jaguar prehispanico", "jaguar_prehispanico.fbx", ROOM_PANTEON, {41.65f, 0.0f, 7.0f}, {0.0f, -90.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Campana de difuntos", "campana_de_difuntos.fbx", ROOM_PANTEON, {44.1f, 2.45f, -11.9f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_METALICO },
	{ "Rebozo de seda", "rebozo_de_seda.fbx", ROOM_PANTEON, {39.025f, 0.57f, -18.2f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Libro de rezos", "libro_de_rezos.fbx", ROOM_PANTEON, {35.525f, 0.57f, -18.2f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Rosario colonial", "rosario_colonial.fbx", ROOM_PANTEON, {37.275f, 1.92f, -18.2f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_METALICO },
	{ "Puerta del panteon izquierda", "Door.fbx", ROOM_PANTEON, {22.66f, 0.0f, -1.01f}, {0.0f, 180.0f, 0.0f}, {0.01241f, 0.01763f, 0.012f}, MAT_MATE },
	{ "Puerta del panteon derecha", "Door.fbx", ROOM_PANTEON, {22.66f, 0.0f, 1.01f}, {0.0f, 180.0f, 0.0f}, {0.01241f, 0.01763f, 0.012f}, MAT_MATE },

	// sala transporte
	{ "Pedestal transporte 1", "pedestal_transporte.fbx", ROOM_TRANSPORTE, {6.55f, 0.0f, 15.00f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Pedestal transporte 2", "pedestal_transporte.fbx", ROOM_TRANSPORTE, {8.15f, 0.0f, 15.00f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Pedestal transporte 3", "pedestal_transporte.fbx", ROOM_TRANSPORTE, {11.00f, 0.0f, 15.00f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Pedestal transporte 4", "pedestal_transporte.fbx", ROOM_TRANSPORTE, {7.30f, 0.0f, 20.30f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Pedestal transporte 5", "pedestal_transporte.fbx", ROOM_TRANSPORTE, {9.60f, 0.0f, 20.30f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Pedestal transporte 6", "pedestal_transporte.fbx", ROOM_TRANSPORTE, {11.90f, 0.0f, 20.30f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Maqueta del Metro", "maqueta_metro.fbx", ROOM_TRANSPORTE, {6.55f, 0.8f, 15.00f}, {0.0f, 90.0f, 0.0f}, {1.15f, 1.15f, 1.15f}, MAT_PLASTICO },
	{ "Maqueta del Tren Ligero", "maqueta_tren_ligero.fbx", ROOM_TRANSPORTE, {8.15f, 0.8f, 15.00f}, {0.0f, 90.0f, 0.0f}, {1.05f, 1.05f, 1.05f}, MAT_PLASTICO },
	{ "Maqueta del Metrobus", "maqueta_metrobus.fbx", ROOM_TRANSPORTE, {11.00f, 0.8f, 15.00f}, {0.0f, 90.0f, 0.0f}, {1.15f, 1.15f, 1.15f}, MAT_PLASTICO },
	{ "Maqueta del Trolebus", "maqueta_trolebus.fbx", ROOM_TRANSPORTE, {7.30f, 0.8f, 20.30f}, {0.0f, -90.0f, 0.0f}, {1.15f, 1.15f, 1.15f}, MAT_PLASTICO },

	// mariposas
	{ "Mariposa monarca", "mariposa_monarca.fbx", ROOM_LOBBY, {0.0f, 2.2f, -2.8f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, MAT_MATE },
	{ "Mariposa monarca 1", "mariposa_monarca.fbx", ROOM_LOBBY, {3.0f, 2.3f, 0.0f}, {-15.0f, 0.0f, 0.0f}, {1.25f, 1.25f, 1.25f}, MAT_MATE },
	{ "Mariposa monarca 2", "mariposa_monarca.fbx", ROOM_LOBBY, {1.5f, 2.7f, 2.6f}, {-15.0f, -60.0f, 0.0f}, {1.25f, 1.25f, 1.25f}, MAT_MATE },
	{ "Mariposa monarca 3", "mariposa_monarca.fbx", ROOM_LOBBY, {-1.5f, 3.0f, 2.6f}, {-15.0f, -120.0f, 0.0f}, {1.25f, 1.25f, 1.25f}, MAT_MATE },
	{ "Mariposa monarca 4", "mariposa_monarca.fbx", ROOM_LOBBY, {-3.0f, 2.5f, 0.0f}, {-15.0f, -180.0f, 0.0f}, {1.25f, 1.25f, 1.25f}, MAT_MATE },
	{ "Mariposa monarca 5", "mariposa_monarca.fbx", ROOM_LOBBY, {-1.5f, 2.9f, -2.6f}, {-15.0f, -240.0f, 0.0f}, {1.25f, 1.25f, 1.25f}, MAT_MATE },
	{ "Mariposa monarca 6", "mariposa_monarca.fbx", ROOM_LOBBY, {1.5f, 2.4f, -2.6f}, {-15.0f, -300.0f, 0.0f}, {1.25f, 1.25f, 1.25f}, MAT_MATE },

	// puerta banos 
	{ "Puerta de los banos", "Door.fbx", ROOM_LOBBY, {18.55f, 0.0f, 19.035f}, {0.0f, 90.0f, 0.0f}, {0.01346f, 0.0128f, 0.012f}, MAT_MATE },
};

// Iluminacion nombre, posicion, color, potencia, alcance
struct LightEntry {
	const char* name;
	glm::vec3   position;
	glm::vec3   color;
	float       power;
	float       range;
};

const glm::vec3 LUZ_CANDIL(1.0f, 0.78f, 0.50f);   // vela
const glm::vec3 LUZ_FAROL(1.0f, 0.86f, 0.62f);    //farol

const LightEntry kLucesMuseo[] = {
	// Velas
	{ "Candil Juguetes oeste",      {-17.15f, 4.2f,  17.65f}, LUZ_CANDIL, 2.0f, 11.0f },
	{ "Candil Juguetes este",       { -8.75f, 4.2f,  17.65f}, LUZ_CANDIL, 2.0f, 11.0f },
	{ "Candil vestibulo",           {  0.0f,  4.2f,  17.65f}, LUZ_CANDIL, 1.6f, 11.0f },
	{ "Candil tienda",              {  9.6f,  4.2f,  17.65f}, LUZ_CANDIL, 1.6f, 11.0f },
	{ "Candil Dia de Muertos sur",  { 17.9f,  4.2f,   7.7f }, LUZ_CANDIL, 2.0f, 11.0f },
	{ "Candil Dia de Muertos norte",{ 17.9f,  4.2f,  -0.7f }, LUZ_CANDIL, 2.0f, 11.0f },
	{ "Velas de la ofrenda",        { 18.0f,  1.8f,  -5.6f }, LUZ_CANDIL, 1.5f, 6.0f },
	{ "Candil Gastronomia sur",     {-18.4f,  4.2f,   6.35f}, LUZ_CANDIL, 2.0f, 11.0f },
	{ "Candil Gastronomia norte",   {-18.4f,  4.2f,  -6.35f}, LUZ_CANDIL, 2.0f, 11.0f },
	{ "Candil Lucha oeste",         {  6.65f, 4.2f, -17.9f }, LUZ_CANDIL, 2.0f, 11.0f },
	{ "Candil Lucha ring",          { 11.9f,  4.2f, -18.2f }, LUZ_CANDIL, 2.4f, 11.0f },
	{ "Candil Lucha este",          { 17.5f,  4.2f, -17.9f }, LUZ_CANDIL, 2.0f, 11.0f },
	{ "Candil pasillo norte",       {  0.0f,  4.2f, -17.9f }, LUZ_CANDIL, 1.6f, 11.0f },
	{ "Candil Xochimilco oeste",    {-18.4f,  4.2f, -17.9f }, LUZ_CANDIL, 2.0f, 11.0f },
	{ "Candil Xochimilco este",     { -8.75f, 4.2f, -17.9f }, LUZ_CANDIL, 2.0f, 11.0f },

	// Focos 
	{ "Foco bodega sur",            { 20.3f,  2.6f,  14.8f }, LUZ_FAROL, 1.6f, 6.0f },
	{ "Foco bodega norte",          { 20.3f,  2.6f, -11.1f }, LUZ_FAROL, 1.6f, 6.0f },

	// Faroles 
	{ "Farol jardin NO",            { -2.24f, 3.6f,  -2.24f}, LUZ_FAROL, 2.2f, 10.0f },
	{ "Farol jardin NE",            {  2.24f, 3.6f,  -2.24f}, LUZ_FAROL, 2.2f, 10.0f },
	{ "Farol jardin SO",            { -2.24f, 3.6f,   2.24f}, LUZ_FAROL, 2.2f, 10.0f },
	{ "Farol jardin SE",            {  2.24f, 3.6f,   2.24f}, LUZ_FAROL, 2.2f, 10.0f },
	{ "Farol entrada oeste",        { -3.64f, 3.1f,  24.22f}, LUZ_FAROL, 2.2f, 10.0f },
	{ "Farol entrada este",         {  3.64f, 3.1f,  24.22f}, LUZ_FAROL, 2.2f, 10.0f },

	// Panteon
	{ "Farol paso panteon 1",       { 24.15f, 4.4f,  -1.61f}, LUZ_FAROL, 1.8f, 8.0f },
	{ "Farol paso panteon 2",       { 26.25f, 4.4f,  -1.61f}, LUZ_FAROL, 1.8f, 8.0f },
	{ "Velas de la capilla",        { 37.1f,  1.5f, -21.6f }, LUZ_CANDIL, 2.0f, 8.0f },
	{ "Farol panteon 1",            { 35.8f,  2.8f, -10.5f }, LUZ_FAROL, 2.4f, 9.0f },
	{ "Farol panteon 2",            { 38.4f,  2.8f, -10.5f }, LUZ_FAROL, 2.4f, 9.0f },
	{ "Farol panteon 3",            { 35.07f, 3.0f,  -2.0f }, LUZ_FAROL, 2.4f, 9.0f },
	{ "Farol panteon 4",            { 39.13f, 3.0f,  -2.0f }, LUZ_FAROL, 2.4f, 9.0f },
	{ "Farol panteon 5",            { 35.07f, 3.0f,   2.0f }, LUZ_FAROL, 2.4f, 9.0f },
	{ "Farol panteon 6",            { 39.13f, 3.0f,   2.0f }, LUZ_FAROL, 2.4f, 9.0f },
	{ "Farol panteon 7",            { 35.8f,  2.8f,  10.5f }, LUZ_FAROL, 2.4f, 9.0f },
	{ "Farol panteon 8",            { 38.4f,  2.8f,  10.5f }, LUZ_FAROL, 2.4f, 9.0f },
};

// Luna 
const glm::vec3 MOON_DIRECTION = glm::normalize(glm::vec3(-0.3f, -0.8f, -0.5f));  // direccion luz
const glm::vec3 MOON_COLOR(0.34f, 0.38f, 0.52f);
const glm::vec3 NIGHT_AMBIENT(0.08f, 0.085f, 0.115f);

// Protagonista
const char* const PLAYER_MODEL_FILE = "models/protagonista/protagonista_catrina.fbx";
const float PLAYER_WALK_FRAMES = 32.0f;  // caminata
const float PLAYER_REST_FRAME = 40.0f;

// Mariachi con huesos (caminata hecha en Meshy AI), camina por el vestibulo
const char* const MARIACHI_MODEL_FILE = "models/mariachi/mariachi.fbx";
const float MARIACHI_FRAMES = 35.0f;   // cuadros del ciclo de caminata
const float MARIACHI_FPS = 30.0f;
const glm::vec3 MARIACHI_POSITION(0.0f, 0.0f, 17.5f);

// Muneca bailarina (esqueleto y baile hechos en Blender), en la mesa libre de la tienda
const char* const MUNECA_BAILE_FILE = "models/muneca_baile/muneca_baile.fbx";
const float MUNECA_BAILE_FRAMES = 60.0f;
const float MUNECA_BAILE_FPS = 30.0f;
const glm::vec3 MUNECA_BAILE_POSITION(-18.2f, 0.9f, 17.5f);   // reposo

// Maquetas animadas en Blender (sala transporte)
// Cablebus: la cabina avanza y regresa por el cable
const char* const CABLEBUS_ANIM_FILE = "models/maqueta_cablebus_animada/maqueta_cablebus_animada.fbx";
const float CABLEBUS_ANIM_FRAMES = 180.0f;
const float CABLEBUS_ANIM_FPS = 30.0f;
const glm::vec3 CABLEBUS_ANIM_POSITION(9.60f, 0.8f, 20.30f);
// Ecobici: giran las dos ruedas
const char* const ECOBICI_ANIM_FILE = "models/maqueta_ecobici_animada/maqueta_ecobici_animada.fbx";
const float ECOBICI_ANIM_FRAMES = 60.0f;
const float ECOBICI_ANIM_FPS = 30.0f;
const glm::vec3 ECOBICI_ANIM_POSITION(11.90f, 0.8f, 20.30f);

#endif
