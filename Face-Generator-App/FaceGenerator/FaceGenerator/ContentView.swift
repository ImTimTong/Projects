//
//  ContentView.swift
//  FaceGenerator
//
//  Created by user on 5/29/24.
//

import SwiftUI

class ViewModel: ObservableObject {
    @Published var image: Image?
    
    func fetchNewImage() {
        guard let url = URL(string: "https://thispersondoesnotexist.com/") else {
            return
        }
        let task = URLSession.shared.dataTask(with: url) { data, _, _ in
            guard let data = data else { return }
            
            DispatchQueue.main.async {
                guard let uiImage = UIImage(data: data) else {
                    return
                }
                self.image = Image(uiImage: uiImage)
            }
        }
        
        task.resume()
    }
}

struct ContentView: View {
    @StateObject var viewModel = ViewModel()
    
    init() {
        let appearance = UINavigationBar.appearance()
        appearance.titleTextAttributes =  [.foregroundColor: UIColor.systemYellow]
        appearance.largeTitleTextAttributes =  [.foregroundColor: UIColor.systemYellow]
    }
    
    var body: some View {
        NavigationStack {
            GeometryReader { geometry in
            
                VStack {
                    Spacer()
                    if let image = viewModel.image {
                        ZStack {
                            image
                                .resizable()
                                .foregroundStyle(Color.red)
                                .frame(width: 250, height: 250)
                                .padding()
                        }
                        .frame(width: geometry.size.width/1.3, height: geometry.size.width/1.3)
                        .background(Color.green)
                        .shadow(radius: 10)
                    }
                    else {
                        Image(systemName: "face.smiling")
                            .resizable()
                            .foregroundStyle(Color.red)
                            .frame(width: 250, height: 250)
                            .padding()
                    }
                    
                    Spacer()
                    Button(action: {
                        viewModel.fetchNewImage()
                    }, label: {
                        Text("Get a Face")
                            .bold()
                            .frame(width: 200, height: 80)
                            .foregroundStyle(Color.white)
                            .background(Color.black)
                            .clipShape(Capsule())
                            .padding()
                    })
                }
                .frame(width: geometry.size.width, height: geometry.size.height)
                .background(Color.blue)
            }
            //.navigationTitle("Face Generator")
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItem(placement: .principal) {
                    HStack {
                        Spacer()
                        Text("Face Generator")
                            .font(.largeTitle.bold())
                            .foregroundStyle(.yellow)
                        Spacer()
                    }
                }
            }
        }
    }
}

#Preview {
    ContentView()
}
