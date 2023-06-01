from django.contrib import admin
from django.urls import path, include
from . import views
from . import routing

urlpatterns = [
    path('http://127.0.0.1:8000/', views.receive_data_view, name='receive_data'),
    # ...
]

websocket_urlpatterns = routing.websocket_urlpatterns

urlpatterns += [
    path('weather/', include((websocket_urlpatterns, 'weather'))),
]

urlpatterns += [
    path('admin/', admin.site.urls),
]
