from channels.generic.websocket import AsyncWebsocketConsumer

class WeatherConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        # Adăugați codul de autentificare/autorizare, dacă este necesar

        # Înregistrați consumatorul la un grup WebSocket
        await self.channel_layer.group_add('weather_data', self.channel_name)

        # Acceptați conexiunea WebSocket
        await self.accept()

    async def disconnect(self, close_code):
        # Eliminați consumatorul din grupul WebSocket la deconectare
        await self.channel_layer.group_discard('weather_data', self.channel_name)

    async def receive(self, text_data):
        # Primirea datelor de la senzorul meteorologic
        weather_data = json.loads(text_data)

        # Salvarea datelor în baza de date
        WeatherData.objects.create(
            temperature=weather_data['temperature'],
            humidity=weather_data['humidity'],
            pressure=weather_data['pressure'],
            altitude=weather_data['altitude'],
            created_at=weather_data['created_at']
        )

        # Trimiterea datelor actualizate către toți clienții conectați
        await self.channel_layer.group_send(
            'weather_data',
            {
                'type': 'weather_data_update',
                'weather_data': weather_data
            }
        )

    async def weather_data_update(self, event):
        # Trimiterea datelor actualizate către clienții conectați
        weather_data = event['weather_data']
        await self.send(json.dumps(weather_data))
