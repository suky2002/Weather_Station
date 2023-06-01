from django.contrib import admin
from .models import WeatherData

class WeatherDataAdmin(admin.ModelAdmin):
    list_display = ['temperature', 'humidity', 'pressure', 'altitude','created_at']

admin.site.register(WeatherData, WeatherDataAdmin)
