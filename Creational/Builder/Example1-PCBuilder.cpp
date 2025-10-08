#include <iostream>
#include <string>
#include <vector>

class Computer {
    std::string cpu_;
    std::string gpu_;
    int ramGB_{0};
    int storageGB_{0};
    bool liquidCooling_{false};

   public:
    void setCPU(const std::string& cpu) { cpu_ = cpu; }
    void setGPU(const std::string& gpu) { gpu_ = gpu; }
    void setRAM(int gb) { ramGB_ = gb; }
    void setStorage(int gb) { storageGB_ = gb; }
    void setLiquidCooling(bool lc) { liquidCooling_ = lc; }

    void showSpecs() const {
        std::cout << "Computer Specs:\n";
        std::cout << "CPU: " << cpu_ << "\n";
        std::cout << "GPU: " << gpu_ << "\n";
        std::cout << "RAM: " << ramGB_ << "GB\n";
        std::cout << "Storage: " << storageGB_ << "GB\n";
        std::cout << "Liquid Cooling: " << (liquidCooling_ ? "Yes" : "No")
                  << "\n";
    }
};

class ComputerBuilder {
    Computer computer_;

   public:
    ComputerBuilder& setCPU(const std::string& cpu) {
        computer_.setCPU(cpu);
        return *this;
    }
    ComputerBuilder& setGPU(const std::string& gpu) {
        computer_.setGPU(gpu);
        return *this;
    }
    ComputerBuilder& setRAM(int gb) {
        computer_.setRAM(gb);
        return *this;
    }
    ComputerBuilder& setStorage(int gb) {
        computer_.setStorage(gb);
        return *this;
    }
    ComputerBuilder& setLiquidCooling(bool lc) {
        computer_.setLiquidCooling(lc);
        return *this;
    }

    Computer build() { return computer_; }
};

class Director {
    ComputerBuilder& builder_;

   public:
    Director(ComputerBuilder& builder) : builder_(builder) {}

    Computer constructGamingPC() {
        return builder_.setCPU("Intel i9-14900K")
            .setGPU("NVIDIA RTX 5090")
            .setRAM(64)
            .setStorage(2000)
            .setLiquidCooling(true)
            .build();
    }

    Computer constructOfficePC() {
        return builder_.setCPU("Intel i5-14600")
            .setGPU("Integrated Graphics")
            .setRAM(16)
            .setStorage(512)
            .build();
    }

    Computer constructDeveloperPC() {
        return builder_.setCPU("AMD Ryzen 9 7900X")
            .setGPU("NVIDIA RTX 4070")
            .setRAM(32)
            .setStorage(1000)
            .build();
    }
};

int main() {
    ComputerBuilder builder;
    Director director(builder);

    Computer gamingPC{director.constructGamingPC()};
    Computer officePC{director.constructOfficePC()};
    Computer devPC{director.constructDeveloperPC()};

    std::cout << "=== Gaming PC ===\n";
    gamingPC.showSpecs();

    std::cout << "\n=== Office PC ===\n";
    officePC.showSpecs();

    std::cout << "\n=== Developer PC ===\n";
    devPC.showSpecs();

    return 0;
}
