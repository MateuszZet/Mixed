//
//  VideoPlayerViewController.swift
//  apka_lista
//
//  Created by stud on 01.12.2017.
//  Copyright © 2017 stud. All rights reserved.
//

import UIKit
import AVFoundation
import AVKit

class VideoPlayerViewController: AVPlayerViewController {
    
    override func viewDidLoad() {
        super.viewDidLoad()
        let videoURL = URL(string: "https://clips.vorwaerts-gmbh.de/big_buck_bunny.mp4")
        let player = AVPlayer(url: videoURL!)
        let playerViewController = AVPlayerViewController()
        playerViewController.player = player
        self.present(playerViewController, animated: true) {
            playerViewController.player!.play()
        }    }
}
