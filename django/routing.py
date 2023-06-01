from django.urls import re_path
from . import views
from . import consumers

urlpatterns = [
    re_path(r'^receive_data/$', views.receive_data_view, name='receive_data'),
]

websocket_urlpatterns = [
    re_path(r'ws/weather/$', consumers.WeatherConsumer.as_asgi()),
]