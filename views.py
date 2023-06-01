from django.http import JsonResponse
from django.views.generic import View
from django.http import HttpResponse
from django.db import connection

def receive_data_view(request):
    # Connect to the MySQL database
    with connection.cursor() as cursor:
        # Execute a query to fetch data from a table
        cursor.execute("SELECT * FROM esp32_mc_db")
        data = cursor.fetchall()

    # Process the retrieved data
    # ...

    return HttpResponse("Data received and processed successfully.")



class RealTimeDataView(View):
    def get(self, request, *args, **kwargs):
        with connection.cursor() as cursor:
            cursor.execute('SELECT * FROM esp32_mc_db')
            data = cursor.fetchall()
        
        # Process data as per your requirements
        # Prepare the data in a format suitable for chart generation
        
        return JsonResponse(data, safe=False)  # Return the data as JSON response
