# Museo Interactivo de la Ciudad de México

Proyecto final de **Computación Gráfica e Interacción Humano-Computadora** (Facultad de Ingeniería, UNAM, semestre 2027-1, Ing. José Ramón Pérez Athié).

Un museo virtual que se recorre de noche, ambientado en Día de Muertos, hecho con **OpenGL 3.3, GLSL, GLFW, GLM y Assimp**. Tema del curso: *México y su cultura*.

## Qué tiene

- Una hacienda con seis salas: Juguetes y Tradiciones, Día de Muertos, Gastronomía, Lucha Libre, Xochimilco y Transporte. Están alrededor de un jardín central, y un pasillo con puerta abierta lleva a un panteón.
- 137 piezas en FBX, que usan 124 modelos distintos. El equipo modeló en Blender la hacienda y 111 de esos modelos.
- Skybox nocturno con cube mapping y 35 luces puntuales con atenuación.
- Materiales con Phong (mates y plásticos) y con Fresnel (metálicos y translúcidos).
- 27 animaciones por código: 12 básicas, 7 por keyframes y 8 procedurales.
- 2 personajes con huesos: la protagonista y un mariachi.
- Una muñeca con esqueleto y baile hechos en Blender.
- Dos maquetas animadas en Blender: la cabina del Cablebús recorre su cable y las ruedas de la Ecobici giran.
- 16 piezas que se pueden tomar, girar, mover y escalar.
- 2 interacciones con las luces en tiempo real, y una tecla que pausa las animaciones.

## Fases del proyecto

Cada fase está en **Releases** como un `.zip` con el código, los modelos, las DLL y el ejecutable. Para correr cualquiera: descomprime el zip y abre `MuseoCDMX/bin/ProyectoMuseo.exe`.

| Fase | Release | Qué agregamos |
|---|---|---|
| 1 | `fase-1-modelos` | Hacienda, piezas cargadas desde una tabla, protagonista y tres cámaras |
| 2 | `fase-2-iluminacion` | Iluminación nocturna: candiles, faroles, luna y atenuación |
| 3 | `fase-3-materiales` | Materiales mates y plásticos con Phong, metálicos y translúcidos con Fresnel |
| 4 | `fase-4-animaciones` | Animaciones básicas, por keyframes y procedurales |
| 5 | `fase-5-interacciones` | 16 piezas interactivas con anillo amarillo |
| 6 | `fase-6-entrega-lab` | Versión entregada en el laboratorio |
| 7 | `fase-7-huesos-y-teclas` | Protagonista y mariachi con huesos, muñeca animada, teclas L, K y P |
| 8 | `fase-8-panteon` | Panteón con sus piezas y luces, campana y tecolote animados |
| 9 | `fase-9-transporte` | Sala de Transporte, muñeca en Juguetes y guitarra interactiva |
| 10 | `fase-10-maquetas-animadas` | Cablebús y Ecobici animados en Blender (versión final, la de este repositorio) |

Requisitos: Windows 10 u 11 de 64 bits, tarjeta de video con OpenGL 3.3 y 4 GB de RAM.

## Compilar

1. Instala Visual Studio 2022 con la carga de trabajo **Desarrollo para el escritorio con C++**.
2. Abre `project/ProyectoMuseo/ProyectoMuseo.sln`.
3. Elige **Release** y **x64**, y compila con Compilar > Compilar solución.
4. El ejecutable queda en `bin/ProyectoMuseo.exe`, junto a `models`, `shaders` y `textures`. Ábrelo desde ahí o con F5.

Las bibliotecas (GLAD, GLFW, GLM y Assimp) ya vienen en `deps/` y las DLL en `bin/`. No hay que instalar nada más.

## Controles

| Tecla | Acción |
|---|---|
| W A S D / Shift / mouse | Caminar o volar / correr / mirar |
| F1 / F2 / F3 | Primera persona / tercera persona / cámara libre |
| Q / E | Bajar / subir (cámara libre) |
| L / K | Apagar o prender las luces / cambiar su color |
| P | Pausar o reanudar la animación de la pieza de enfrente |
| F / R / flechas / 2-1 / Z-X / Retroceso | Tomar, girar, mover, subir o bajar, escalar y regresar la pieza interactiva |
| T / F11 / M N B / Esc | Techos / pantalla completa / modo de malla / salir |

## Estructura

```
ProyectoMuseo.cpp        programa principal
include/                 clases (shader, cámara, modelo, modelo animado) y tablas del museo
                         (catálogo, animaciones, interacciones)
bin/                     ejecutable, DLL, shaders, modelos FBX y texturas
deps/                    GLAD, GLFW, GLM y Assimp
project/ProyectoMuseo/   solución de Visual Studio 2022
```

## Origen de los modelos

- **Equipo:** la hacienda y 111 de los 124 modelos de piezas, modelados en Blender.
- **Meshy AI:** 11 piezas (los dos alebrijes, la calabaza en tacha, la canasta de frutas, el catrín, la catrina, los dos luchadores, la máscara clásica, la olla de frijoles y la marioneta), la muñeca Lele y los modelos y caminatas de la protagonista y del mariachi.
- **Material del laboratorio:** la puerta (práctica 09). Las clases de `include/` parten de las prácticas del curso, basadas en LearnOpenGL.

## Equipo

- Escobar Díaz Víctor Manuel
- Hernández Rubio Josué
- Jiménez Torres Edgar Ulises
- Reyes Vázquez Fernando
