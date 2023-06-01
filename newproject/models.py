from django.db import models

class WeatherData(models.Model):
    temperature = models.DecimalField(max_digits=5, decimal_places=2)
    humidity = models.DecimalField(max_digits=5, decimal_places=2)
    pressure = models.DecimalField(max_digits=6, decimal_places=2)
    altitude = models.DecimalField(max_digits=6, decimal_places=2)
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f'Temperature: {self.temperature}, Humidity: {self.humidity}, Pressure: {self.pressure}, Altitude: {self.altitude}, Created At: {self.created_at}'
    class Meta:
        managed = False
        db_table = 'esp32_table_testt'  # Specify the correct table name
