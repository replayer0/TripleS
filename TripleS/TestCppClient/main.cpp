#include <stdio.h>
#include "CustomClient.h"

void main()
{
    CustomClient client;
    client.Initialize();
    client.Run();
    client.Release();
}