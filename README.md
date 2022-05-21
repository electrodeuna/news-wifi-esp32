# Portal de Noticias

Proyecto IoT (Internet de las Cosas) para obtener las noticias del dia usando el Nodemcu Esp32 y una pantalla oled de 0.96 pulgadas, obteniendo la información de una Api publica.

Video Tutorial:

https://www.youtube.com/watch?v=HEfFj0GpdZQ

## Componentes

- Nodemcu Esp32
- Pantalla Oled 0.96"
- 2 botones
- Interruptor
- Placa perforada
- Bateria
- Cables

## Crear API Key

News API es una HTTP REST API para buscar y recuperar articulos de todas los portales de noticias de la web. Para obtener los articulo necesitamos una Api Key propia que la obtenemos ingresando a la pagina de News Api: 

https://newsapi.org/

Nos creamos un usuario y una vez logueados hacemos click en "Get API Key"

![image](https://user-images.githubusercontent.com/85527788/169649663-03571ac5-5e7f-4ea8-9d39-11174b2b41e5.png)

Esta Api Key la usaremos para reemplazarla en el codigo (Linea 24)

![image](https://user-images.githubusercontent.com/85527788/169649788-d6689683-86e9-4562-bbad-7c1003ed127f.png)

En la linea 73 podemos reemplazar en el link el "country=ar" por el pais que queremos (ar(Argentina), co (Colombia), mx (Mexico), ve (Venezuela))

![image](https://user-images.githubusercontent.com/85527788/169649871-a706a728-c06b-4e98-b395-41327470ac3e.png)
