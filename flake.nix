{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }: 
  let 
    system = "x86_64-linux";
    pkgs = import nixpkgs { inherit system; };
  in
  {
    packages.${system}.default = pkgs.mkShellNoCC {
      packages = with pkgs; [
            pkgsCross.i686-embedded.buildPackages.gccWithoutTargetLibc
            nasm
            bear
        ];
      shellHook = ''
        export PATH=${pkgs.lib.makeBinPath (with pkgs; [ qemu grub2 xorriso ])}:$PATH
      '';
    };
  };
}
