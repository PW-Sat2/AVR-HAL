#include <hal/hal>

using namespace hal;

static EepromStorage<int> eepromVariable;

int main() {
    Serial0.init(115200);
    Serial0.redirect_stdio();
    Serial0.redirect_stderr();

    while (1) {
        printf("Choose: r - read, w - write: ");
        char c;
        scanf("%c", &c);
        printf("\n");

        if (c == 'r') {
            int readed = eepromVariable;
            printf("Read: %d\n", readed);
        }
        if (c == 'w') {
            int val;
            scanf("%d", &val);
            eepromVariable = val;
        }
    }
}
