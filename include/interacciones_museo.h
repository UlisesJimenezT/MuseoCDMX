#ifndef INTERACCIONES_MUSEO_H
#define INTERACCIONES_MUSEO_H

const float INTERACT_DISTANCE = 2.5f;   
const float INTERACT_ROTATE_SPEED = 90.0f;  
const float INTERACT_MOVE_SPEED = 0.8f;     
const float INTERACT_SCALE_SPEED = 0.5f;    
const float INTERACT_MIN_SCALE = 0.3f, INTERACT_MAX_SCALE = 2.5f;

// Piezas interaccion
const char* const kPiezasInteractivas[] = {
	// Sala juguetes
	"Balero", "Carrito de madera", "Tren de juguete",
	// Sala dia de muertos
	"Calavera de azucar", "Pan de muerto", "Jarrito de barro",
	// Sala gastronomia
	"Taza de chocolate", "Molcajete", "Jarra de pulque", "Molinillo",
	// Sala lucha 
	"Mascara azul", "Mascara roja", "Trofeo",
	// Sala xochi
	"Canasta de flores", "Ajolote",
	// Panteon
	"Guitarra de Paracho",
};

#endif
